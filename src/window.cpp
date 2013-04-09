#include "window.h"

Window::Window(Config* example_config, const QVector<RendererGUI *> &supported_cuts, QWidget *_parent) :
    QMainWindow(_parent)
{
    setWindowTitle("Simulus");
    resize(800, 1);

    mdi_area = new QMdiArea(this);
    mdi_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdi_area->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    connect(mdi_area, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(mdiChangeSubWindow(QMdiSubWindow*)));

    initCuts(supported_cuts);

    // create example project
    project = new Project;

    /*
     *  Create example model
     */
    // Renderers
    QStringList example_renderers;
    example_renderers << "HPPloupe";
    example_renderers << "GrayScale";

    // Model
    Model *example_model = project->addModel(example_renderers, example_config);
    current_model = example_model;

    // MDI
    QtSimpleBuffer *example_buffer = new QtSimpleBuffer();
    QMdiSubWindow *example_mdisubwindow = project->addWindowToModel(example_model, example_buffer);

    // TODO: global follow line
    //connect(example_container, SIGNAL(imclosing(QMdiSubWindow*)), this, SLOT(mdiClosingWindow(QMdiSubWindow*)));
    connect(WindowEvent::get(), &WindowEvent::mdiWindowClosing, [=](QMdiSubWindow *win) { project->removeWindowFromModel(win); });

    mdi_area->addSubWindow(example_mdisubwindow);
    mdi_area->currentSubWindow()->showMaximized();

    main_layout = new QVBoxLayout;

    tmp_dock_layout = new QGridLayout;
    tmp_dock_widget = createCutConfigBar();
    tmp_dock_layout->addWidget(tmp_dock_widget, 0, 0);
    QWidget *please_remove_me = new QWidget;
    please_remove_me->setLayout(tmp_dock_layout);
    QSplitter *spl_cut = new QSplitter;
    spl_cut->addWidget(mdi_area);
    spl_cut->addWidget(please_remove_me);


    createMenuBar();
    main_layout->addWidget(spl_cut);
    main_layout->addLayout(createPlayerBar());

    QWidget *central_widget = new QWidget;
    central_widget->setLayout(main_layout);
    setCentralWidget(central_widget);

    updateIterationCounter(Config::FORCED_UPDATE);
    connect(WindowEvent::get(), SIGNAL(requireRepaint()), this, SLOT(updateIterationCounter()));
}

void Window::initCuts(const QVector<RendererGUI *>& supported_cuts)
{
    last_selected_cut = NULL;
    for(RendererGUI* cut_widget : supported_cuts) {
        cuts[cut_widget->getName()] = cut_widget;
    }
}

void Window::createMenuBar()
{
    /*
     *  Menu TODO:
     *
     *  Add shortcuts
     *  Add "open recent project"
     *  Add model menus
     *  Enable/disable menus when MDISubWindow activated/deactivated
     *
     */

    /*
     *  Project
     */
    QMenu *mnu_file = menuBar()->addMenu(tr("&File"));

    // New Project
    QAction *act_project_new = new QAction(QIcon::fromTheme("document-new"), tr("&New Project"), this);
    act_project_new->setShortcut(QKeySequence::New);
    connect(act_project_new, SIGNAL(triggered()), this, SLOT(actProjectNew()));
    mnu_file->addAction(act_project_new);

    // Open Project
    QAction *act_project_open = new QAction(QIcon::fromTheme("document-open"), tr("&Open Project..."), this);
    act_project_open->setShortcut(QKeySequence::Open);
    connect(act_project_open, SIGNAL(triggered()), this, SLOT(actProjectOpen()));
    mnu_file->addAction(act_project_open);

    // Close Project
    QAction *act_project_close = new QAction(QIcon::fromTheme("window-close"), tr("Close Project"), this);
    connect(act_project_close, SIGNAL(triggered()), this, SLOT(actProjectNew()));
    mnu_file->addAction(act_project_close);

    mnu_file->addSeparator();

    // Save Project
    QAction *act_project_save = new QAction(QIcon::fromTheme("document-save"), tr("&Save Project"), this);
    act_project_save->setShortcut(QKeySequence::Save);
    connect(act_project_save, SIGNAL(triggered()), this, SLOT(actProjectSave()));
    mnu_file->addAction(act_project_save);

    // Save Project As...
    QAction *act_project_saveas = new QAction(QIcon::fromTheme("document-save-as"), tr("Save Project As..."), this);
    act_project_saveas->setShortcut(QKeySequence::SaveAs);
    connect(act_project_saveas, SIGNAL(triggered()), this, SLOT(actProjectSaveAs()));
    mnu_file->addAction(act_project_saveas);

    mnu_file->addSeparator();

    // Quit
    QAction *act_quit = new QAction(QIcon::fromTheme("application-exit"), tr("&Quit"), this);
    act_quit->setShortcut(QKeySequence::Quit);
    connect(act_quit, SIGNAL(triggered()), this, SLOT(actQuit()));
    mnu_file->addAction(act_quit);

    /*
     *  Model
     */
    QMenu *mnu_model = menuBar()->addMenu(tr("&Model"));

    //  Load new model
    QAction *act_model_load = new QAction(QIcon::fromTheme("list-add"), tr("&Load model"), this);
    act_model_load->setShortcut(tr("Ctrl+L"));
    connect(act_model_load, SIGNAL(triggered()), this, SLOT(actModelLoad()));
    mnu_model->addAction(act_model_load);

    // Split model view
    QAction *act_model_split = new QAction(QIcon::fromTheme("insert-object"), tr("Split view"), this);
    connect(act_model_split, SIGNAL(triggered()), this, SLOT(actModelSplit()));
    mnu_model->addAction(act_model_split);

    /*
     *  Help
     */
    QMenu *mnu_help = menuBar()->addMenu(tr("&About"));

    // About me ;)
    QAction *act_about_me = new QAction(tr("About Simulus"), this);
    connect(act_about_me, &QAction::triggered, [=](){ QMessageBox::about(this, tr("About Simulus"), tr("This is <b>SIMULUS</b>!")); });
    mnu_help->addAction(act_about_me);

    // About Qt
    QAction *act_about_qt = new QAction(tr("About Qt"), this);
    connect(act_about_qt, &QAction::triggered, [=](){ qApp->aboutQt(); });
    mnu_help->addAction(act_about_qt);

    QToolBar *tlb_test = new QToolBar(this);
    tlb_test->addAction(act_project_new);
    tlb_test->addAction(act_project_save);
    tlb_test->addAction(act_project_open);
    tlb_test->addAction(act_model_load);
    tlb_test->addAction(act_model_split);
    addToolBar(tlb_test);
}

QWidget* Window::createCutConfigBar()
{
    QLabel *lbl_cut_switch_label = new QLabel(tr("View:"));

    cmb_cut_switch = new QComboBox;
    connect(cmb_cut_switch, SIGNAL(currentIndexChanged(QString)), this, SLOT(updateRendererConfigLayout(QString)));
    cmb_cut_switch->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred));

    QHBoxLayout *lay_cut_config_bar = new QHBoxLayout;
    lay_cut_config_bar->addWidget(lbl_cut_switch_label);
    lay_cut_config_bar->addWidget(cmb_cut_switch);

    QVBoxLayout *lay_cut_config_all = new QVBoxLayout;
    lay_cut_config_all->addLayout(lay_cut_config_bar);
    for(QMap<QString, RendererGUI*>::Iterator it = cuts.begin(); it != cuts.end(); ++it) {
        it.value()->getWidget()->setVisible(false);
        lay_cut_config_all->addWidget(it.value()->getWidget());
        cmb_cut_switch->addItem(it.key());
    }
    lay_cut_config_all->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));

    QWidget *tmp_widget = new QWidget(this);
    tmp_widget->setLayout(lay_cut_config_all);
    return tmp_widget;
}

QHBoxLayout* Window::createPlayerBar()
{
    player_timer.setInterval(500);
    connect(&player_timer, SIGNAL(timeout()), this, SLOT(nextIteration()));

    // TODO: repacle by render area refresh button
    btn_player_prev = createButtonFromIcon(":/icons/media-skip-backward.png", 24, 32);
    connect(btn_player_prev, SIGNAL(clicked()), this, SLOT(prevIteration()));
    btn_player_start = createButtonFromIcon(":/icons/media-playback-start.png", 24, 32);
    connect(btn_player_start, SIGNAL(clicked()), this, SLOT(playerSwitch()));
    btn_player_next = createButtonFromIcon(":/icons/media-skip-forward.png", 24, 32);
    connect(btn_player_next, SIGNAL(clicked()), this, SLOT(nextIteration()));

    lbl_iteration = new QLabel("?/?");
    lbl_iteration->setFixedHeight(32);

    sld_progress = new QSlider(Qt::Horizontal);
    sld_progress->setMinimum(0);
    sld_progress->setMaximum(0);
    connect(sld_progress, SIGNAL(valueChanged(int)), this, SLOT(setIteration(int)));

    QHBoxLayout *lay_player_bar = new QHBoxLayout;
    lay_player_bar->addWidget(btn_player_prev);
    lay_player_bar->addWidget(btn_player_start);
    lay_player_bar->addWidget(btn_player_next);
    lay_player_bar->addWidget(sld_progress);
    lay_player_bar->addWidget(lbl_iteration);
    return lay_player_bar;
}

void Window::playerSwitch()
{
    if(player_timer.isActive()) {
        player_timer.stop();
        btn_player_start->setIcon(QIcon(":/icons/media-playback-start.png"));
    } else {
        player_timer.start();
        btn_player_start->setIcon(QIcon(":/icons/media-playback-pause.png"));
    }
}

void Window::nextIteration() {
    QMdiSubWindow *current_mdi = mdi_area->currentSubWindow();
    if(current_mdi == NULL) return ;
    updateIterationCounter(current_model->config->nextIteration());
}

void Window::prevIteration() {
    QMdiSubWindow *current_mdi = mdi_area->currentSubWindow();
    if(current_mdi == NULL) return ;
    updateIterationCounter(current_model->config->prevIteration());
}

void Window::setIteration(int iteration) {
    QMdiSubWindow *current_mdi = mdi_area->currentSubWindow();
    if(current_mdi == NULL) return ;
    updateIterationCounter(current_model->config->setIteration(iteration));
}

void Window::updateIterationCounter(int iteration)
{
    if(current_model == NULL) return ;

    // TODO: move FORCED_UPDATE into Config and remove following condition
    if(iteration == Config::FORCED_UPDATE || iteration != sld_progress->value() || iteration == 0) {
        if(iteration == Config::FORCED_UPDATE) iteration = sld_progress->value();
        sld_progress->setValue(iteration);
        qDebug() << "[window/update] call redrawing all buffers";
        current_model->drawAll();

        /*
        for(auto it : tmp_buffers) {
            visualizator->buffer = it.first;
            visualizator->config = it.second;
            visualizator->draw();
        }
        */
    }
    sld_progress->setMaximum(current_model->config->getIterationsCount());
    lbl_iteration->setText(QString::number(sld_progress->value()) + QString(" / ") + QString::number(sld_progress->maximum()));
}

void Window::updateRendererConfigLayout(const QString &new_layout_name)
{
    qDebug() << "[window/???] need to update layout: " << new_layout_name;
    if(last_selected_cut) last_selected_cut->setVisible(false);
    last_selected_cut = cuts[new_layout_name]->getWidget();
    last_selected_cut->setVisible(true);
    //current_model->renderer = cuts[new_layout_name]->getRenderer();
    //current_model->setWindowRenderer(mdi_area->currentSubWindow(), cuts[new_layout_name]->getRenderer());
}

void Window::mdiChangeSubWindow(QMdiSubWindow *win)
{
    if(win == NULL) {
        current_model = NULL;
        if(tmp_dock_widget) {
            tmp_dock_layout->removeWidget(tmp_dock_widget);
            tmp_dock_widget->hide();
        }
        tmp_dock_widget = NULL;

    } else {
        current_model = project->getModel(win);
        if(tmp_dock_widget) {
            tmp_dock_layout->removeWidget(tmp_dock_widget);
            tmp_dock_widget->hide();
        }
        tmp_dock_widget = current_model->getRenderersGUI(win);
        tmp_dock_layout->addWidget(tmp_dock_widget, 0, 0);
        tmp_dock_widget->show();
    }

    qDebug() << "[window/mdichange] new model" << current_model << "from subwin" << win;
}

void Window::mdiClosingWindow(QMdiSubWindow *win)
{
    project->removeWindowFromModel(win);
}

void Window::actProjectNew()
{

}

bool Window::actProjectOpen()
{
    if(project != NULL) {
        // TODO some question
        delete project;
    }
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Project"));
    if(filename.isNull()) return true;
    project = new Project;
    project->load(filename, mdi_area);
    current_model = project->getModel(mdi_area->activeSubWindow());
    qDebug() << "[windows/open] current_model after load =" << current_model;
    // current_model->renderer = cuts[cmb_cut_switch->currentText()]->getRenderer();
    //current_model->setWindowRenderer(mdi_area->currentSubWindow(), cuts[cmb_cut_switch->currentText()]->getRenderer());
    return true;
}

bool Window::actProjectClose()
{
    if(project) {
        int q = QMessageBox::question(this, tr("Do you want to save project before closing?"), tr("Save Project"), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if(q == QMessageBox::Yes && !actProjectSave()) q = QMessageBox::Cancel;
        if(q == QMessageBox::Cancel) return false;
    }
    delete project;
    project = NULL;
    return true;
}

bool Window::actProjectSave()
{
    QString filename = project->getFilename();
    if(filename.isEmpty())
        return actProjectSaveAs();
    project->save(filename);
    return true;
}

bool Window::actProjectSaveAs()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save Project As..."));
    if(filename.isNull()) return false;
    project->save(filename);
    return true;
}

void Window::actModelLoad()
{
    QString modelFileName = QFileDialog::getOpenFileName(this, tr("Load model"));
    if(modelFileName.isNull()) return ;

    // Renderers
    QStringList example_renderers;
    example_renderers << "HPPloupe";
    example_renderers << "GrayScale";
    example_renderers << "Wave";

    // Config
    DLLConfig *dll_config = new DLLConfig(modelFileName.toStdString().c_str());
    //loading_model->config = dynamic_cast<Config*>(dll_config);

    // Model
    Model *loading_model = project->addModel(example_renderers, dll_config);
    //loading_model->renderer = current_model->renderer;

    // MDI
    QtSimpleBuffer* qt_buffer = new QtSimpleBuffer();
    QMdiSubWindow *q = project->addWindowToModel(loading_model, qt_buffer);
    /*
    loading_model->addWindow(q, qt_buffer, cuts.begin().value()->getRenderer());
    project->addModel(q, loading_model);
    */
    qDebug() << "[window/newmode] add window" << q;
    mdi_area->addSubWindow(q);
    //qt_buffer->render_window->showMaximized();
    q->showMaximized();
    current_model = loading_model;

}

void Window::actModelSplit()
{
    QtSimpleBuffer *buf = new QtSimpleBuffer();
    QMdiSubWindow *win = project->addWindowToModel(current_model, buf);
    qDebug() << "[window/main] created mdisubwin" << win;
    mdi_area->addSubWindow(win);
    win->showMaximized();
    win->update();
}

void Window::actQuit()
{
    if(!actProjectClose()) return ;
    qApp->quit();
}
