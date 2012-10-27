#include "window.h"

Window::Window(Visualizzzator *vis, QWidget *parent) : QMainWindow(parent) {
	setWindowTitle("Simple Qt render");
	resize(800, 600);

	render_area = new RenderArea(vis);

	QHBoxLayout *lay_buttons = new QHBoxLayout;
	QVBoxLayout *lay_main = new QVBoxLayout;

	QPushButton *btn_render = new QPushButton("render");
	btn_render->setMaximumWidth(200);
	connect(btn_render, SIGNAL(clicked()), render_area, SLOT(setNextFrame()));
	connect(btn_render, SIGNAL(clicked()), render_area, SLOT(repaint()));
	lay_buttons->addWidget(btn_render);

	QPushButton *btn_quit = new QPushButton("quit");
	btn_quit->setMaximumWidth(200);
	connect(btn_quit, SIGNAL(clicked()), qApp, SLOT(quit()));
	lay_buttons->addWidget(btn_quit);

	lay_main->addWidget(render_area);
	//lay_main->addLayout(lay_buttons);
	lay_main->addLayout(createPlayerBar());

	QWidget *central_widget = new QWidget;
	central_widget->setLayout(lay_main);
	setCentralWidget(central_widget);
}

void Window::createMenuBar() {

}

QHBoxLayout* Window::createPlayerBar() {
	player_timer.setInterval(1);
	connect(&player_timer, SIGNAL(timeout()), this, SLOT(playNextFrame()));

	btn_player_start = new QPushButton;
	//btn_backward->setIcon(QIcon("images/player/start.png"));
	btn_player_start->setFixedSize(32, 32);
	connect(btn_player_start, SIGNAL(clicked()), this, SLOT(playerSwitch()));

	sld_progress = new QSlider(Qt::Horizontal);
	sld_progress->setMinimum(0);
	sld_progress->setMaximum(0);
	connect(sld_progress, SIGNAL(valueChanged(int)), render_area, SLOT(setFrame(int)));
	connect(sld_progress, SIGNAL(valueChanged(int)), render_area, SLOT(repaint()));

	QHBoxLayout *lay_player_bar = new QHBoxLayout;
	lay_player_bar->addWidget(btn_player_start);
	lay_player_bar->addWidget(sld_progress);
	return lay_player_bar;
}

void Window::resetConfig(Config *config) {
	playerStop();
	sld_progress->setMaximum(config->getFramesCount());
	sld_progress->setValue(0);
}

void Window::playerSwitch() {
	if(player_timer.isActive())
		player_timer.stop();
	else
		player_timer.start();
}
