#pragma once

#include <QtWidgets>
#include "../buffer.h"
#include "renderarea.h"
#include "openglarea.h"

class QtSimpleBuffer : public GraphicBuffer
{
    QtSimpleBuffer(const QtSimpleBuffer& );
    QtSimpleBuffer& operator=(const QtSimpleBuffer& );

    /*
     *  Buffer objects
     */
    QImage *image;
    QPainter *painter;
#ifndef BUFFER_OPENGL
    RenderArea *render_area;
#else
    OpenGLArea *render_area;
#endif
    QScrollBar *scb_render_width, *scb_render_height;
    QScrollArea *scroll_area;

    /*
     *  Buffer parameters
     */
    bool use_xscroll, use_yscroll;

public:
    // TODO: fix hack
    QWidget *render_window;

    QtSimpleBuffer();
    virtual ~QtSimpleBuffer();

    virtual void create();
    virtual void prepare();
    virtual void complete();

    virtual void setXScroll(int max_value, int current_value = SCROLL_PREVIOUS_VALUE);
    virtual int  getXScroll() const { return scb_render_width->value(); }
    virtual void setYScroll(int max_value, int current_value = SCROLL_PREVIOUS_VALUE);
    virtual int  getYScroll() const { return scb_render_height->value(); }

    virtual QPainter* getRawPaintDevice() { return painter; }

    virtual int width() const { return render_area->width(); }
    virtual int height() const { return render_area->height(); }
};
