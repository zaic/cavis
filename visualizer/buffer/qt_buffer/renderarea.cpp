#include "renderarea.h"

RenderArea::RenderArea(Visualizzzator *vis, QWidget *parent) : QWidget(parent), visualizator(vis) {

}

void RenderArea::paintEvent(QPaintEvent *event) {
	QPainter painter(this);
	painter.setPen(Qt::black);
	painter.fillRect(0, 0, width(), height(), Qt::white);
	painter.drawRect(0, 0, width() - 1, height() - 1);

	/*
	static int xshift = 0;
	xshift += 10;
	painter.drawLine(10 + xshift, 20, 20 + xshift, 40);
	*/

	QtSimpleBuffer buffer(&painter);
	(*visualizator)(buffer);
}
