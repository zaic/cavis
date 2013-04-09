#pragma once

#include <QtWidgets>
#include "windowevent.h"

class BufferContainer : public QWidget
{
    Q_OBJECT

    QVBoxLayout *layhi;
    QWidget *buf;
    QMdiSubWindow *just_mdi_sub_window;

public:
    explicit BufferContainer(QWidget *init_widget, QMdiSubWindow *mdiwin, QWidget *_parent = 0);

    void closeEvent(QCloseEvent *);
    void resizeEvent(QResizeEvent *);
    
signals:
    void imclosing(QMdiSubWindow*);
    
public slots:
    
};
