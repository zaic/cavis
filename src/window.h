#pragma once

#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSlider>
#include <QTimer>
#include <QLabel>
#include <QDebug>
#include "buffer/buffer.h"
#include "config/config.h"
#include "visualizzzator.h"
#include "buffer/qt_buffer/qtsimplebuffer.h"

class Window : public QMainWindow {
	Q_OBJECT

	void createMenuBar();
	QHBoxLayout* createPlayerBar();

	QAction *act_open, *act_quit;
	QAction *act_about;

	/*
	 *	Plyaer bar
	 */
	QPushButton *btn_player_prev;	// go by one iteration back
	QPushButton *btn_player_start;	// start/pause button
	QPushButton *btn_player_next;	// go by one iteration forward;
	QSlider *sld_progress;
	QLabel *lbl_frame;
	QTimer player_timer;

	Visualizzzator *visualizator;
	Config *config;
	GraphicBuffer *buffer;

public:
	explicit Window(Visualizzzator *vis, QWidget *parent = 0);
	
signals:
	
public slots:
	// player toolbar
	void playerStart() { player_timer.start(); }
	void playerStop() { player_timer.stop(); }
	void playerSwitch();
	// main actions to control process
	void nextFrame();
	void prevFrame();
	void setFrame(int frame);
	// update current frame value in slider and label
	void updateFramesCounter(int frame = Config::FRAME_NOT_CHANGED);
};
