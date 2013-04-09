#pragma once

#include <QtCore>
#include <QtGui>
#include <QtWidgets>

#include "windowevent.h"
#include "buffercontainer.h"
#include "buffer/buffer.h"
#include "config/config.h"
#include "renderer/gui.h"
#include "buffer/qt_buffer/qtsimplebuffer.h"
#include "common.h"
#include "workspace/project.h"

#include "config/dll/dllconfig.h"

class Window : public QMainWindow
{
    Q_OBJECT

    QVBoxLayout *main_layout;
    //QAction *act_open, *act_quit;
    //QAction *act_about;

    /*
     *	MDI
     */
    void createMenuBar();
    QMdiArea *mdi_area;
    QTreeWidget *wgt_project_tree;

    QGridLayout *tmp_dock_layout;
    QWidget *tmp_dock_widget;

    /*
     *	Cut config bar
     */
    void initCuts(const QVector<RendererGUI *>& supported_cuts);
    QWidget *createCutConfigBar();

    QMap<QString, RendererGUI*> cuts;
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
    QLabel *lbl_iteration;
    QTimer player_timer;

    /*
     *  Project
     */
    Project *project;
    Model *current_model;
    //QMap<BufferContainer*, QMdiSubWindow*> mdi_subwindows;

public:
    explicit Window(Config *example_config, const QVector<RendererGUI *>& supported_cuts, QWidget *_parent = 0);

signals:

public slots:
    // MDI
    void mdiChangeSubWindow(QMdiSubWindow *win);
    void mdiClosingWindow(QMdiSubWindow *win);

    // renderer config toolbar
    void updateRendererConfigLayout(const QString& new_layout_name);

    // player toolbar
    void playerStart() { player_timer.start(); }
    void playerStop() { player_timer.stop(); }
    void playerSwitch();

    // main actions to control process
    void nextIteration();
    void prevIteration();
    void setIteration(int iteration);

    // update current iteration value in slider and label
    void updateIterationCounter(int iteration = Config::FORCED_UPDATE);

    /*
     *  Menu
     */
    void actProjectNew();
    bool actProjectOpen();
    bool actProjectClose();
    bool actProjectSave();
    bool actProjectSaveAs();

    void actModelLoad();
    void actModelSplit();

    void actQuit();
};
