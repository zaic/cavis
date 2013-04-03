#pragma once

#include "renderer/renderer.h"
#include "common.h"
#include "config/config.h"
#include <algorithm>

class GrayScaleRenderer : public Renderer
{
    Q_OBJECT

    GrayScaleRenderer(const GrayScaleRenderer& );
    GrayScaleRenderer& operator=(const GrayScaleRenderer& );

public:
    Q_INVOKABLE GrayScaleRenderer();
    virtual ~GrayScaleRenderer();

    virtual void draw() override;
};
