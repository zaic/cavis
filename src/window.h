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
#include <QComboBox>
#include <QMap>
#include "windowevent.h"
#include "buffer/buffer.h"
#include "config/config.h"
#include "cut/gui.h"
#include "visualizzzator.h"
#include "buffer/qt_buffer/qtsimplebuffer.h"

class Window : public QMainWindow {
	Q_OBJECT

	void createMenuBar();

	QVBoxLayout *main_layout;
	QAction *act_open, *act_quit;
	QAction *act_about;

	/*
	 *	Cut config bar
	 */
	void initCuts(const QVector<CutGUI *>& supported_cuts);
	QVBoxLayout* createCutConfigBar();

	QMap<QString, QWidget*> cuts;
	QWidget *last_selected_cut;
	QComboBox *cmb_cut_switch;

	/*
	 *	Plyaer bar
	 */
	QHBoxLayout* createPlayerBar();

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
	explicit Window(Visualizzzator *vis, const QVector<CutGUI *>& supported_cuts, QWidget *_parent = 0);
	
signals:
	
public slots:
	// cut config toolbar
	void updateCutConfigLayout(const QString& new_layout_name);

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
