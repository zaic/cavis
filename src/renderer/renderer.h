#pragma once

#include "common.h"
#include "config/config.h"
#include "buffer/buffer.h"
#include <QtGui/QLayout>

class RendererGUI;

class Renderer
{
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

    virtual void draw() = 0;
};
