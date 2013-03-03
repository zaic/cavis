#pragma once

#include "../common.h"

class GraphicBuffer {
	GraphicBuffer(const GraphicBuffer& );
	GraphicBuffer& operator=(const GraphicBuffer& );

protected:
	GraphicBuffer();

public:
	virtual ~GraphicBuffer();

	// гарантированно вызывается визуализатором до того, как начнётся что-либо рисоваться
	virtual void create() = 0;
	// должно вызываться непосредственно Renderer'ом
	virtual void prepare(int real_width = -1, int real_height = -1, int shift_x = -1, int shift_y = -1) = 0;
	// вызывается визуализатором после того, как Renderer нарисовался
	virtual void complete() = 0;

	virtual int width() const = 0;
	virtual int height() const = 0;

	// TODO migrate to QPainter ?
	virtual void setColor(uint color) = 0;

	virtual void drawPixel(int x, int y) = 0;
	virtual void drawLine(int x0, int y0, int x1, int y1) = 0;
	virtual void drawText(int x, int y, const char *text) = 0;
};
