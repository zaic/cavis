#pragma once

#include <QPainter>
#include <QScrollBar>
#include <QGridLayout>
#include "../buffer.h"
#include "renderarea.h"

class QtSimpleBuffer : public GraphicBuffer {
	QtSimpleBuffer(const QtSimpleBuffer& );
	QtSimpleBuffer& operator=(const QtSimpleBuffer& );

	QImage *image;
	QPainter *painter;
	QWidget *render_window;
	QScrollBar *scb_render_width, *scb_render_height;
	RenderArea *render_area;

private:
	int shift_x, shift_y;
	void setupScrollBar(QScrollBar *render_scroll_bar, int real_size, int window_size, int shift);

public:
	QtSimpleBuffer();
	virtual ~QtSimpleBuffer() { delete render_window; }

	virtual bool prepare(int real_width = -1, int real_height = -1, int shift_x_ = -1, int shift_y_ = -1);
	virtual void complete();

	virtual int width() const { return render_area->width(); }
	virtual int height() const { return render_area->height(); }

	virtual void setColor(uint color);

	virtual void drawPixel(int x, int y);
};
