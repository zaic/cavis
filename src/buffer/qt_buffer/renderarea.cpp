#include "renderarea.h"

RenderArea::RenderArea(QWidget *_parent) : QWidget(_parent), buffer_image(NULL)
{

}

void RenderArea::paintEvent(QPaintEvent* )
{
	QPainter painter(this);
	painter.setPen(Qt::black);
	painter.fillRect(0, 0, width(), height(), Qt::white);
	painter.drawRect(0, 0, width() - 1, height() - 1);
	if(buffer_image) {
		painter.drawImage(this->rect(), *(this->buffer_image));
	}

	/*
	static int xshift = 0;
	xshift += 10;
	painter.drawLine(10 + xshift, 20, 20 + xshift, 40);
	*/
}

void RenderArea::drawImage(QImage *image)
{
	buffer_image = image;
	this->update();
}
