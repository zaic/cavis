#pragma once

#include "../renderer.h"
#include "../../common.h"
#include "../../config/config.h"
#include <algorithm>
#include <QDebug>

class GrayScaleRenderer : public Renderer
{
	GrayScaleRenderer(const GrayScaleRenderer& );
	GrayScaleRenderer& operator=(const GrayScaleRenderer& );

public:
	GrayScaleRenderer();
	virtual ~GrayScaleRenderer();

	virtual void draw();
};
