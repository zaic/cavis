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

    // create example model
    QtSimpleBuffer *example_buffer = new QtSimpleBuffer();
    QMdiSubWindow *example_mdisubwindow = mdi_area->addSubWindow(example_buffer->render_window);
    mdi_area->currentSubWindow()->showMaximized();
    Model* example_model = new Model;
    example_model->buffer = example_buffer;
    example_model->config = example_config;
    example_model->renderer = supported_cuts.first()->getRenderer();
    project->addModel(example_mdisubwindow, example_model);
    current_model = example_model;

    main_layout = new QVBoxLayout;

    QSplitter *spl_cut = new QSplitter;
    spl_cut->addWidget(mdi_area);
    spl_cut->addWidget(createCutConfigBar());

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
    QMenu *mnu_file = menuBar()->addMenu(tr("&File"));
    mnu_file->addAction("New Project");
    mnu_file->addAction("Open Project");
    mnu_file->addSeparator();
    mnu_file->addAction("Quit");

    /*
     *  Model
     */
    QMenu *mnu_model = menuBar()->addMenu(tr("&Model"));
    //  Load new model
    QAction *act_model_load = new QAction(this);
    act_model_load->setText("Load model...");
    connect(act_model_load, SIGNAL(triggered()), this, SLOT(actModelLoad()));
    mnu_model->addAction(act_model_load);

    QMenu *mnu_help = menuBar()->addMenu(tr("&About"));
    mnu_help->addAction(tr("About Simulus"));
    mnu_help->addAction(tr("&About Qt"));
}

QWidget* Window::createCutConfigBar()
{
    QLabel *lbl_cut_switch_label = new QLabel(tr("Renderer:"));
    //lbl_cut_switch_label->setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred));

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
    // TODO: move FORCED_UPDATE into Config and remove following condition
    if(iteration == Config::FORCED_UPDATE || iteration != sld_progress->value() || iteration == 0) {
        if(iteration == Config::FORCED_UPDATE) iteration = sld_progress->value();
        sld_progress->setValue(iteration);
        current_model->draw();

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
    qDebug() << "need to update layout: " << new_layout_name;
    if(last_selected_cut) last_selected_cut->setVisible(false);
    last_selected_cut = cuts[new_layout_name]->getWidget();
    last_selected_cut->setVisible(true);
    current_model->renderer = cuts[new_layout_name]->getRenderer();
}

void Window::mdiChangeSubWindow(QMdiSubWindow *win)
{
    current_model = project->getModel(win);
}

void Window::actModelLoad()
{
    QString modelFileName = QFileDialog::getOpenFileName(this, tr("Load model"));
    if(modelFileName.isNull()) return ;

    Model *loading_model = new Model;
    loading_model->renderer = current_model->renderer;

    DLLConfig *dll_config = new DLLConfig(modelFileName.toStdString().c_str());
    loading_model->config = dynamic_cast<Config*>(dll_config);

    QtSimpleBuffer* qt_buffer = new QtSimpleBuffer();
    loading_model->buffer = dynamic_cast<GraphicBuffer*>(qt_buffer);
    QMdiSubWindow *q = mdi_area->addSubWindow(qt_buffer->render_window);
    project->addModel(q, loading_model);
    qt_buffer->render_window->showMaximized();

    current_model = loading_model;
}
