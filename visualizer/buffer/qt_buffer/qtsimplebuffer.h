#pragma once

#include <QPainter>
#include "../buffer.h"

class QtSimpleBuffer : public GraphicBuffer {
	QtSimpleBuffer(const QtSimpleBuffer& );
	QtSimpleBuffer& operator=(const QtSimpleBuffer& );

	QPainter *painter;

public:
	QtSimpleBuffer(QPainter *_painter) : GraphicBuffer(), painter(_painter) { }
	virtual ~QtSimpleBuffer() { }

	virtual int getX() const { return painter->window().width(); }
	virtual int getY() const { return painter->window().height(); }

	virtual void setColor(uint color);

	virtual void drawPixel(int x, int y);
};
