#pragma once

#include <QtCore>
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

    bool save(QDataStream& stream);
    bool load(QDataStream& stream);

    // TODO: group to windows(?) and create list
    GraphicBuffer *buffer;
    Config *config;
    Renderer *renderer;
    // TODO: renderers list
};
