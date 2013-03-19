#pragma once

#include "buffer/buffer.h"
#include "config/config.h"
#include "renderer/renderer.h"

class Model
{
    Model(const Model& );
    Model& operator=(const Model& );

public:
    Model();
    ~Model();

    void draw();

    GraphicBuffer *buffer;
    Config *config;
    Renderer *renderer;
    // TODO: renderers list
};
