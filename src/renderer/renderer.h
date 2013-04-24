#pragma once

#include "common.h"
#include "config/config.h"
#include "buffer/buffer.h"
#include <QtGui>

class RendererGUI;

class Renderer : public QObject
{
    Q_OBJECT

    Renderer(const Renderer& );
    Renderer& operator=(const Renderer& );

protected:
    Renderer();
    Config *config;
    GraphicBuffer *buffer;

public:
    virtual ~Renderer();

    virtual void setParameters(RendererGUI *) { }

    virtual void setConfig(Config *_config) { config = _config; }
    virtual void setBuffer(GraphicBuffer *_buffer) { buffer = _buffer; }
    virtual Config* getConfig() const { return config; }
    virtual GraphicBuffer* getBuffer() const { return buffer; }

    virtual void prepare() = 0;
    virtual void draw(void *device) = 0;
    virtual QString getBufferFormat() const { return "simple"; }
};
