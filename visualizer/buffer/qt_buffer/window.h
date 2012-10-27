#pragma once

#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSlider>
#include <QTimer>
#include "renderarea.h"
#include "../../config/config.h"

class Window : public QMainWindow {
	Q_OBJECT

	void createMenuBar();
	QHBoxLayout* createPlayerBar();

	QAction *act_open, *act_quit;
	QAction *act_about;

	// player bar
	QPushButton *btn_player_start;
	QSlider *sld_progress;
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
	
};
