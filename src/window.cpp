#include "window.h"

Window::Window(Visualizzzator *vis, const QVector<CutGUI *>& supported_cuts, QWidget *_parent) : QMainWindow(_parent), visualizator(vis), config(vis->config) {
	setWindowTitle("Simulus");
	resize(800, 1);

	mdi_area = new QMdiArea(this);
	mdi_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	mdi_area->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

	initCuts(supported_cuts);
	QtSimpleBuffer* qt_buffer = new QtSimpleBuffer();
	buffer = qt_buffer;
	mdi_area->addSubWindow(qt_buffer->render_area);

	QHBoxLayout *lay_buttons = new QHBoxLayout;
	main_layout = new QVBoxLayout;

	QPushButton *btn_render = new QPushButton("render");
	btn_render->setMaximumWidth(200);
	//connect(btn_render, SIGNAL(clicked()), render_area, SLOT(setNextFrame()));
	//connect(btn_render, SIGNAL(clicked()), render_area, SLOT(repaint()));
	lay_buttons->addWidget(btn_render);

	QPushButton *btn_quit = new QPushButton("quit");
	btn_quit->setMaximumWidth(200);
	connect(btn_quit, SIGNAL(clicked()), qApp, SLOT(quit()));
	lay_buttons->addWidget(btn_quit);

	QSplitter *spl_cut = new QSplitter;
	spl_cut->addWidget(mdi_area);
	spl_cut->addWidget(createCutConfigBar());

	// TODO: must be fixed
	// cut-config-specific panel must be inserted after combobox
	createMenuBar();
	//main_layout->addWidget(mdi_area);
	//main_layout->addLayout(lay_buttons);
	//main_layout->insertLayout(0, createCutConfigBar());
	//main_layout->removeItem(lay_buttons);
	main_layout->addWidget(spl_cut);
	main_layout->addLayout(createPlayerBar());

	QWidget *central_widget = new QWidget;
	central_widget->setLayout(main_layout);
	setCentralWidget(central_widget);

	updateFramesCounter();

	connect(WindowEvent::get(), SIGNAL(requireRepaint()), this, SLOT(updateFramesCounter(Config::FRAME_FORCED_UPDATE)));
}

void Window::initCuts(const QVector<CutGUI *>& supported_cuts) {
	last_selected_cut = NULL;

#if 1
	for(CutGUI* cut_widget : supported_cuts) {
		cuts[cut_widget->name()] = cut_widget;
	}
#else
	QPushButton *btn_one = new QPushButton("i'm one");
	QHBoxLayout *lay_one = new QHBoxLayout;
	lay_one->addWidget(btn_one);
	QWidget *wgt_one = new QWidget;
	wgt_one->setLayout(lay_one);
	cuts["HPP Loupe"] = wgt_one;

	QPushButton *btn_two = new QPushButton("i'm button");
	QHBoxLayout *lay_two = new QHBoxLayout;
	lay_two->addWidget(btn_two);
	QWidget *wgt_two = new QWidget;
	wgt_two->setLayout(lay_two);
	cuts["Rounding"] = wgt_two;
#endif
}

void Window::createMenuBar() {
	QMenu *mnu_file = menuBar()->addMenu(tr("&File"));
	mnu_file->addAction("New Project");
	mnu_file->addAction("Open Project");
	mnu_file->addSeparator();
	mnu_file->addAction("Quit");

	QMenu *mnu_model = menuBar()->addMenu(tr("&Model"));
	mnu_model->addSeparator();

	QMenu *mnu_help = menuBar()->addMenu(tr("&About"));
	mnu_help->addAction(tr("About Simulus"));
	mnu_help->addAction(tr("&About Qt"));
}

QWidget* Window::createCutConfigBar() {
	QLabel *lbl_cut_switch_label = new QLabel("Cut:");
	//lbl_cut_switch_label->setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred));

	cmb_cut_switch = new QComboBox;
	connect(cmb_cut_switch, SIGNAL(currentIndexChanged(QString)), this, SLOT(updateCutConfigLayout(QString)));
	cmb_cut_switch->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred));

	QHBoxLayout *lay_cut_config_bar = new QHBoxLayout;
	lay_cut_config_bar->addWidget(lbl_cut_switch_label);
	lay_cut_config_bar->addWidget(cmb_cut_switch);

	QVBoxLayout *lay_cut_config_all = new QVBoxLayout;
	lay_cut_config_all->addLayout(lay_cut_config_bar);
	//for(const pair<QString, QWidget*>& cut : cuts) {
	for(QMap<QString, CutGUI*>::Iterator it = cuts.begin(); it != cuts.end(); ++it) {
		it.value()->widget()->setVisible(false);
		lay_cut_config_all->addWidget(it.value()->widget());
		cmb_cut_switch->addItem(it.key());
	}
	lay_cut_config_all->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));

	QWidget *tmp_widget = new QWidget(this);
	tmp_widget->setLayout(lay_cut_config_all);
	return tmp_widget;
}

QHBoxLayout* Window::createPlayerBar() {
	player_timer.setInterval(500);
	connect(&player_timer, SIGNAL(timeout()), this, SLOT(nextFrame()));

	btn_player_prev = new QPushButton;
	btn_player_prev->setFixedSize(32, 32);
	connect(btn_player_prev, SIGNAL(clicked()), this, SLOT(prevFrame()));

	btn_player_start = new QPushButton;
	//btn_backward->setIcon(QIcon("images/player/start.png"));
	btn_player_start->setFixedSize(32, 32);
	connect(btn_player_start, SIGNAL(clicked()), this, SLOT(playerSwitch()));

	btn_player_next = new QPushButton;
	btn_player_next->setFixedSize(32, 32);
	connect(btn_player_next, SIGNAL(clicked()), this, SLOT(nextFrame()));

	lbl_frame = new QLabel("?/?");
	lbl_frame->setFixedHeight(32);

	sld_progress = new QSlider(Qt::Horizontal);
	sld_progress->setMinimum(0);
	sld_progress->setMaximum(0);
	/*
	connect(sld_progress, SIGNAL(valueChanged(int)), render_area, SLOT(setFrame(int)));
	connect(sld_progress, SIGNAL(valueChanged(int)), this, SLOT(updateFramesCounter()));
	connect(sld_progress, SIGNAL(valueChanged(int)), render_area, SLOT(repaint()));
	*/
	connect(sld_progress, SIGNAL(valueChanged(int)), this, SLOT(setFrame(int)));

	QHBoxLayout *lay_player_bar = new QHBoxLayout;
	lay_player_bar->addWidget(btn_player_prev);
	lay_player_bar->addWidget(btn_player_start);
	lay_player_bar->addWidget(btn_player_next);
	lay_player_bar->addWidget(sld_progress);
	lay_player_bar->addWidget(lbl_frame);
	return lay_player_bar;
}

void Window::playerSwitch() {
	if(player_timer.isActive())
		player_timer.stop();
	else
		player_timer.start();
}

void Window::prevFrame() {
	updateFramesCounter(config->prevFrame());
}

void Window::nextFrame() {
	updateFramesCounter(config->nextFrame());
}

void Window::setFrame(int frame_id) {
	updateFramesCounter(config->setFrame(frame_id));
}

void Window::updateFramesCounter(int frame) {
	if(frame == Config::FRAME_FORCED_UPDATE || (frame != Config::FRAME_NOT_CHANGED /*&& frame != sld_progress->value()*/)) {
		sld_progress->setValue(frame);
		visualizator->draw(buffer);
	}
	sld_progress->setMaximum(config->getFramesCount());
	lbl_frame->setText(QString::number(sld_progress->value()) + QString(" / ") + QString::number(sld_progress->maximum()));
}

void Window::updateCutConfigLayout(const QString &new_layout_name) {
	qDebug() << "need update layout: " << new_layout_name;
	if(last_selected_cut) last_selected_cut->setVisible(false);
	last_selected_cut = cuts[new_layout_name]->widget();
	last_selected_cut->setVisible(true);
	visualizator->cut = cuts[new_layout_name]->getCut();
}
