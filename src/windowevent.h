#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QMdiSubWindow>

class WindowEvent : public QObject
{
    Q_OBJECT

    explicit WindowEvent(QObject *_parent = NULL);
    WindowEvent(const WindowEvent&);
    WindowEvent& operator=(const WindowEvent&);

public:
    ~WindowEvent();

    static WindowEvent* get();

    void doRequireRepaint() { emit requireRepaint(); }
    void doProjectChanged() { emit projectChanged(); }
    void doMdiWindowClosing(QMdiSubWindow *win) { emit doMdiWindowClosing(win); }

signals:
    void requireRepaint();
    void projectChanged();
    void mdiWindowClosing(QMdiSubWindow*);

public slots:

};
