#pragma once

#include "../renderer.h"
#include "../../common.h"
#include "../../config/config.h"
#include <algorithm>
#include <QDebug>

using std::min;

class HPPLoupeRenderer : public Renderer {
	int cell_size;
	int shift_x, shift_y;

	bool autoscale;
	int scale_cell_size;

public:
	HPPLoupeRenderer();
	virtual ~HPPLoupeRenderer();

	void setAutoscale(bool value) { autoscale = value; }
	void setScale(int value) { scale_cell_size = value; }

	virtual void draw();
};
