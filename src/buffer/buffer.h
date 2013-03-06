#pragma once

#include "../common.h"

class GraphicBuffer
{
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

	// поддержка скроллинга
	static const int SCROLL_DISABLE = -1807;
	static const int SCROLL_PREVIOUS_VALUE = -2911;
	// TODO: AUTO and set it by default. и можно ещё enum запилить.
	virtual void setXScroll(int max_value, int current_value = SCROLL_PREVIOUS_VALUE) = 0;
	virtual int  getXScroll() const = 0;
	virtual void setYScroll(int max_value, int current_value = SCROLL_PREVIOUS_VALUE) = 0;
	virtual int  getYScroll() const = 0;

	// возвращается непосредственно объект, для которого сделана обёртка
	virtual void* getRawPaintDevice() = 0;

	// ширина видимой для рисования площади
	virtual int width() const = 0;
	// высота видимой для рисования площади
	virtual int height() const = 0;

	// актуально, когда надо рисовать, игнорируя полосы прокрутки
	virtual int getX(int x) const { return x; }
	virtual int getY(int y) const { return y; }

	virtual void setColor(uint color) = 0;

	virtual void drawPixel(int x, int y) = 0;
	virtual void drawLine(int x0, int y0, int x1, int y1) = 0;
	virtual void drawText(int x, int y, const char *text) = 0;
};
