#include "qtsimplebuffer.h"

QtSimpleBuffer::QtSimpleBuffer() : GraphicBuffer(), shift_x(0), shift_y(0) {
	render_area = new RenderArea;
	scb_render_height = new QScrollBar(Qt::Vertical);
	scb_render_width = new QScrollBar(Qt::Horizontal);
	render_window = new QWidget;

	QGridLayout *lay_main = new QGridLayout;
	//lay_main->setSpacing(1);
	lay_main->addWidget(render_area, 0, 0);
	lay_main->addWidget(scb_render_height, 0, 1);
	lay_main->addWidget(scb_render_width, 1, 0);
	render_window->setLayout(lay_main);

	// TODO: fix hack
#if 0
	render_window->show();
	render_window->resize(800, 600);
#endif
}

void QtSimpleBuffer::setupScrollBar(QScrollBar *render_scroll_bar, int real_size, int window_size, int shift) {
	if(real_size <= 0 || real_size <= window_size) {
		render_scroll_bar->setEnabled(false);
		return ;
	}
	render_scroll_bar->setEnabled(true);
	render_scroll_bar->setRange(0, real_size - window_size);
	render_scroll_bar->setValue(shift);
}

void QtSimpleBuffer::create() {
	// TODO
}

void QtSimpleBuffer::prepare(int real_width, int real_height, int shift_x_, int shift_y_) {
	// TODO: add some exceptions

	// set scrollbars
#if 0
	if(shift_x_ >= 0)
		shift_x = shift_x_;
	if(shift_y_ >= 0)
		shift_y = shift_y_;
#else
	shift_x = scb_render_width->value();
	shift_y = scb_render_height->value();
#endif
	// TODO rewrite to reference (shift_x, shift_y)?
	setupScrollBar(scb_render_width, real_width, render_area->width(), shift_x);
	setupScrollBar(scb_render_height, real_height, render_area->height(), shift_y);
	shift_x = scb_render_width->isEnabled() ? scb_render_width->value() : 0;
	shift_y = scb_render_height->isEnabled() ? scb_render_height->value() : 0;

	// set render area
	// TODO SMART POINTERS!!!!111
	// call new without delete :'(
	image = new QImage(width(), height(), QImage::Format_RGB32);
	if(image == NULL) return ;
	image->fill(Qt::white);

	painter = new QPainter(image);
	if(painter == NULL) return ;
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
	painter->drawPoint(x + 1 - shift_x, y + 1 - shift_y);
}

void QtSimpleBuffer::drawLine(int x0, int y0, int x1, int y1) {
	painter->drawLine(x0, y0, x1, y1);
}

void QtSimpleBuffer::drawText(int x, int y, const char *text) {
	painter->drawText(x, y, text);
}
