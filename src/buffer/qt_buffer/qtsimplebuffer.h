#pragma once

#include <QPainter>
#include "../buffer.h"
#include "renderarea.h"

class QtSimpleBuffer : public GraphicBuffer {
	QtSimpleBuffer(const QtSimpleBuffer& );
	QtSimpleBuffer& operator=(const QtSimpleBuffer& );

	QImage *image;
	QPainter *painter;
	RenderArea *render_area;

public:
	QtSimpleBuffer() : GraphicBuffer() { render_area = new RenderArea; render_area->show(); }
	virtual ~QtSimpleBuffer() { delete render_area; }

	virtual bool prepare();
	virtual void complete();

	virtual int width() const { return render_area->width(); }
	virtual int height() const { return render_area->height(); }

	virtual void setColor(uint color);

	virtual void drawPixel(int x, int y);
};
