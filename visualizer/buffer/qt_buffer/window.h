#pragma once

#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSlider>
#include <QTimer>
#include <QLabel>
#include "renderarea.h"
#include "../../config/config.h"

class Window : public QMainWindow {
	Q_OBJECT

	void createMenuBar();
	QHBoxLayout* createPlayerBar();

	QAction *act_open, *act_quit;
	QAction *act_about;

	/*
	 *	Plyaer bar
	 */
	QPushButton *btn_player_prev;	// go to one iteration back
	QPushButton *btn_player_start;	// start/pause button
	QPushButton *btn_player_next;	// go to one iteration forward;
	QSlider *sld_progress;
	QLabel *lbl_frame;
	QTimer player_timer;

	RenderArea *render_area;

public:
	explicit Window(Visualizzzator *vis, QWidget *parent = 0);
	
signals:
	
public slots:
	void resetConfig(Config *config);
	void playerStart() { player_timer.start(); }
	void playerStop() { player_timer.stop(); }
	void playerSwitch();
	void playNextFrame() { sld_progress->setValue(sld_progress->value() + 1); }
	void playPrevFrame() { sld_progress->setValue(sld_progress->value() - 1); }
	void updateFramesCounter();
};
