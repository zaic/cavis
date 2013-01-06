#include "qtsimplebuffer.h"

bool QtSimpleBuffer::prepare() {
	// TODO SMART POINTERS!!!!111
	// call new, but without delete :'(
	image = new QImage(width(), height(), QImage::Format_RGB32);
	if(image == NULL) return false;
	image->fill(Qt::white);

	painter = new QPainter(image);
	if(painter == NULL) return false;

	return true;
}

void QtSimpleBuffer::complete() {
	delete painter;
	render_area->drawImage(image);
}

void QtSimpleBuffer::setColor(uint color) {
	QColor q_color;
	q_color.setRgba(color);
	painter->setPen(q_color);
}

void QtSimpleBuffer::drawPixel(int x, int y) {
	painter->drawPoint(x + 1, y + 1);
}
