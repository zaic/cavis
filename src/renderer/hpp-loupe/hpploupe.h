#pragma once

#include "renderer/renderer.h"
#include "common.h"
#include "config/config.h"
#include "layer/arrow/arrow.h"
#include <QDebug>

class HPPLoupeRenderer : public Renderer {
	int cell_size;
	int shift_x, shift_y;

	bool autoscale;
	int scale_cell_size;

    ArrowLayer arrow_layer;

public:
	HPPLoupeRenderer();
	virtual ~HPPLoupeRenderer();

	void setAutoscale(bool value) { autoscale = value; }
	void setScale(int value) { scale_cell_size = value; }

	virtual void draw();
};
