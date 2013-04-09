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
    QGridLayout *lay_main;

    QString cur_buffer_type;
    QImage *image;
    QPainter *painter;
    int gl_sizex, gl_sizey;
    float *gl_data;

    RenderArea *render_area_simple;
    OpenGLArea *render_area_opengl;

    QScrollBar *scb_render_width, *scb_render_height;

    /*
     *  Buffer parameters
     */
    bool use_xscroll, use_yscroll;

public:
    // TODO: fix hack
    QWidget *render_window;

    QtSimpleBuffer();
    virtual ~QtSimpleBuffer();

    virtual void create(const QString buffer_type);
    virtual void prepare();
    virtual void complete();

    virtual void setXScroll(int max_value, int current_value = SCROLL_PREVIOUS_VALUE);
    virtual int  getXScroll() const { return scb_render_width->value(); }
    virtual void setYScroll(int max_value, int current_value = SCROLL_PREVIOUS_VALUE);
    virtual int  getYScroll() const { return scb_render_height->value(); }

    virtual QPainter* getRawPaintDevice() { return painter; } // for simple buffer

    virtual void setGLSize(int sx, int sy) { gl_sizex = sx; gl_sizey = sy; } // for gl buffer
    virtual float* getGLData() { return gl_data; }

    virtual int width() const { return render_area_simple->width(); }
    virtual int height() const { return render_area_simple->height(); }

    virtual void update() const;
};
