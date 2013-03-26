#pragma once

#include "buffer/buffer.h"
#include "config/config.h"
#include "renderer/renderer.h"
#include <QtCore>
#include "config/dll/dllconfig.h"

class Model
{
    Model(const Model& );
    Model& operator=(const Model& );

public:
    Model();
    ~Model();

    void draw();

    void save(QDataStream& stream);
    void load(QDataStream& stream);

    // TODO: group to windows(?) and create list
    GraphicBuffer *buffer;
    Config *config;
    Renderer *renderer;
    // TODO: renderers list
};
