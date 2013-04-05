#include "renderarea.h"

RenderArea::RenderArea(QWidget *_parent) : QWidget(_parent), buffer_image(NULL)
{

}

void RenderArea::paintEvent(QPaintEvent* )
{
    //qDebug() << "[buffer/qt] !!!";
    if(!buffer_image) {
        WindowEvent::get()->doRequireRepaint();
        return ;
    }
    QPainter painter(this);
    painter.setPen(Qt::black);
    //qDebug() << "[buffer/qt] renderarea rendering...";
    painter.drawRect(0, 0, width() - 1, height() - 1);
    if(buffer_image) {
        painter.drawImage(this->rect(), *(this->buffer_image));
    }

    delete buffer_image;
    buffer_image = NULL;
    WindowEvent::get()->allowRepaint();
}

void RenderArea::drawImage(QImage *image)
{
    //qDebug() << "[buffer/qt] WANTTODRAWIMAGE";
    buffer_image = image;
#if 0
    this->repaint();
#else
    this->update();
#endif
}
