#include "window.h"

Window::Window(Visualizzzator *vis, const QVector<RendererGUI *> &supported_cuts, QWidget *_parent) : QMainWindow(_parent), visualizator(vis), config(vis->config)
{
    setWindowTitle("Simulus");
    resize(800, 1);

    mdi_area = new QMdiArea(this);
    mdi_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdi_area->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    initCuts(supported_cuts);
    QtSimpleBuffer* qt_buffer = new QtSimpleBuffer();
    buffer = qt_buffer;
    mdi_area->addSubWindow(qt_buffer->render_window);
    mdi_area->currentSubWindow()->showMaximized();

    main_layout = new QVBoxLayout;

    QSplitter *spl_cut = new QSplitter;
    spl_cut->addWidget(mdi_area);
    spl_cut->addWidget(createCutConfigBar());
    tmp_buffers << QPair<GraphicBuffer*, Config*>(buffer, config);

    createMenuBar();
    main_layout->addWidget(spl_cut);
    main_layout->addLayout(createPlayerBar());

    QWidget *central_widget = new QWidget;
    central_widget->setLayout(main_layout);
    setCentralWidget(central_widget);

    updateFramesCounter(Config::FRAME_NOT_CHANGED);

    // TODO: not working, shoul be fixed
    connect(WindowEvent::get(), SIGNAL(requireRepaint()), this, SLOT(updateFramesCounter()));
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
    connect(cmb_cut_switch, SIGNAL(currentIndexChanged(QString)), this, SLOT(updateCutConfigLayout(QString)));
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
    connect(&player_timer, SIGNAL(timeout()), this, SLOT(nextFrame()));

    // TODO: repacle by render area refresh button
    btn_player_prev = createButtonFromIcon(":/icons/media-skip-backward.png", 24, 32);
    connect(btn_player_prev, SIGNAL(clicked()), this, SLOT(prevFrame()));
    btn_player_start = createButtonFromIcon(":/icons/media-playback-start.png", 24, 32);
    connect(btn_player_start, SIGNAL(clicked()), this, SLOT(playerSwitch()));
    btn_player_next = createButtonFromIcon(":/icons/media-skip-forward.png", 24, 32);
    connect(btn_player_next, SIGNAL(clicked()), this, SLOT(nextFrame()));

    lbl_frame = new QLabel("?/?");
    lbl_frame->setFixedHeight(32);

    sld_progress = new QSlider(Qt::Horizontal);
    sld_progress->setMinimum(0);
    sld_progress->setMaximum(0);
    connect(sld_progress, SIGNAL(valueChanged(int)), this, SLOT(setFrame(int)));

    QHBoxLayout *lay_player_bar = new QHBoxLayout;
    lay_player_bar->addWidget(btn_player_prev);
    lay_player_bar->addWidget(btn_player_start);
    lay_player_bar->addWidget(btn_player_next);
    lay_player_bar->addWidget(sld_progress);
    lay_player_bar->addWidget(lbl_frame);
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

void Window::updateFramesCounter(int frame)
{
    if(frame == Config::FRAME_FORCED_UPDATE || frame != Config::FRAME_NOT_CHANGED) {
        if(frame == Config::FRAME_FORCED_UPDATE) frame = sld_progress->value();
        sld_progress->setValue(frame);
        visualizator->buffer = buffer;
        //visualizator->draw();

        for(auto it : tmp_buffers) {
            visualizator->buffer = it.first;
            visualizator->config = it.second;
            visualizator->draw();
        }

    }
    sld_progress->setMaximum(config->getFramesCount());
    lbl_frame->setText(QString::number(sld_progress->value()) + QString(" / ") + QString::number(sld_progress->maximum()));
}

void Window::updateCutConfigLayout(const QString &new_layout_name)
{
    qDebug() << "need to update layout: " << new_layout_name;
    if(last_selected_cut) last_selected_cut->setVisible(false);
    last_selected_cut = cuts[new_layout_name]->getWidget();
    last_selected_cut->setVisible(true);
    visualizator->renderer = cuts[new_layout_name]->getRenderer();
}

void Window::actModelLoad()
{
    QString modelFileName = QFileDialog::getOpenFileName(this, tr("Load model"));
    if(modelFileName.isNull()) return ;

    DLLConfig *dll_config = new DLLConfig(modelFileName.toStdString().c_str());
    config = dynamic_cast<Config*>(dll_config);
    visualizator->config = config;

    QtSimpleBuffer* qt_buffer = new QtSimpleBuffer();
    buffer = qt_buffer;
    mdi_area->addSubWindow(qt_buffer->render_window);
    qt_buffer->render_window->showMaximized();

    tmp_buffers << QPair<GraphicBuffer*, Config*>(buffer, config);
}
