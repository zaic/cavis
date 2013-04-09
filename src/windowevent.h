#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QMdiSubWindow>
#include <QtCore/QDebug>

class WindowEvent : public QObject
{
    Q_OBJECT

    explicit WindowEvent(QObject *_parent = NULL);
    WindowEvent(const WindowEvent&);
    WindowEvent& operator=(const WindowEvent&);

    bool enable_repaint;

public:
    ~WindowEvent();

    static WindowEvent* get();

    void allowRepaint() { enable_repaint = true; }

    void doRequireRepaint() { if(enable_repaint) emit requireRepaint(); enable_repaint = false; }
    void doProjectChanged() { emit projectChanged(); }
    void doMdiWindowClosing(QMdiSubWindow *win) { emit mdiWindowClosing(win); }
    void doProjectTreeChanged() { emit projectTreeChanged(); }

signals:
    void requireRepaint();
    void projectChanged();
    void mdiWindowClosing(QMdiSubWindow*);
    void projectTreeChanged();

public slots:

};
