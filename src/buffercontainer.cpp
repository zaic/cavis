#include "buffercontainer.h"

BufferContainer::BufferContainer(QWidget *init_widget, QMdiSubWindow *mdiwin, QWidget *_parent) :
    QWidget(_parent),
    just_mdi_sub_window(mdiwin)
{
    layhi = new QVBoxLayout;
    if(init_widget) {
        layhi->addWidget(init_widget);
        buf = init_widget;
    }
    layhi->setSpacing(0);
    layhi->setMargin(0);
    setLayout(layhi);
}

void BufferContainer::closeEvent(QCloseEvent *)
{
    WindowEvent::get()->doMdiWindowClosing(just_mdi_sub_window);
}

void BufferContainer::resizeEvent(QResizeEvent *)
{
    //WindowEvent::get()->doRequireRepaint();
}
