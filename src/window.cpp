#include "window.h"

Window::Window(Visualizzzator *vis, QWidget *parent) : QMainWindow(parent), visualizator(vis), config(vis->config) {
	setWindowTitle("Simple Qt render");
	resize(800, 1);

	buffer = new QtSimpleBuffer();

	QHBoxLayout *lay_buttons = new QHBoxLayout;
	QVBoxLayout *lay_main = new QVBoxLayout;

	QPushButton *btn_render = new QPushButton("render");
	btn_render->setMaximumWidth(200);
	//connect(btn_render, SIGNAL(clicked()), render_area, SLOT(setNextFrame()));
	//connect(btn_render, SIGNAL(clicked()), render_area, SLOT(repaint()));
	lay_buttons->addWidget(btn_render);

	QPushButton *btn_quit = new QPushButton("quit");
	btn_quit->setMaximumWidth(200);
	connect(btn_quit, SIGNAL(clicked()), qApp, SLOT(quit()));
	lay_buttons->addWidget(btn_quit);

	//lay_main->addWidget(render_area);
	//lay_main->addLayout(lay_buttons);
	lay_main->addLayout(createPlayerBar());

	QWidget *central_widget = new QWidget;
	central_widget->setLayout(lay_main);
	setCentralWidget(central_widget);

	updateFramesCounter();
}

void Window::createMenuBar() {

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
	if(frame != Config::FRAME_NOT_CHANGED /* && frame != sld_progress->value() */) {
		sld_progress->setValue(frame);
		// TODO prepare buffer (move to vis)
		visualizator->draw(buffer);
		// TODO update image on buffer (move to vis)
	}
	sld_progress->setMaximum(config->getFramesCount());
	lbl_frame->setText(QString::number(sld_progress->value()) + QString(" / ") + QString::number(sld_progress->maximum()));
}
