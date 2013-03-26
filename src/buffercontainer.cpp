#include "buffercontainer.h"

BufferContainer::BufferContainer(QWidget *init_widget, QWidget *parent) :
    QWidget(parent)
{
    layhi = new QVBoxLayout;
    if(init_widget) {
        layhi->addWidget(init_widget);
        buf = init_widget;
    }
    setLayout(layhi);
}

void BufferContainer::closeEvent(QCloseEvent *)
{
    emit imclosing(this);
}
