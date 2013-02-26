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

	virtual void init(Config *_config = NULL, GraphicBuffer *_buffer = NULL);
	virtual void draw(int x, int y);
	virtual void finalize();
};
