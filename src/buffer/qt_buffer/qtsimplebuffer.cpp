#include "qtsimplebuffer.h"

void QtSimpleBuffer::setColor(uint color) {
	QColor q_color;
	q_color.setRgba(color);
	painter->setPen(q_color);
}

void QtSimpleBuffer::drawPixel(int x, int y) {
	painter->drawPoint(x + 1, y + 1);
}
