#pragma once

#include "renderer/renderer.h"
#include "common.h"
#include "config/config.h"
#include <algorithm>

class GrayScaleRenderer : public Renderer
{
    GrayScaleRenderer(const GrayScaleRenderer& );
    GrayScaleRenderer& operator=(const GrayScaleRenderer& );

public:
    GrayScaleRenderer();
    virtual ~GrayScaleRenderer();

    virtual void draw();
};
