#pragma once

#include <QPainter>
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
    virtual void create(const QString buffer_type) = 0;
    // должно вызываться непосредственно Renderer'ом, после того, как все необходимые параметры буфера будут заданые (напр., скроллинг)
    virtual void prepare() = 0;
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
    virtual QPainter* getRawPaintDevice() = 0;
    virtual void setGLSize(int sx, int sy) = 0;
    virtual float* getGLData() = 0;

    // ширина видимой для рисования площади
    virtual int width() const = 0;
    // высота видимой для рисования площади
    virtual int height() const = 0;
};
