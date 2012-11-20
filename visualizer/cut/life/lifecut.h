#pragma once

#include "../cut.h"
#include "../../common.h"
#include "../../config/config.h"
#include <algorithm>

using std::min;

class LifeCut : public Cut2D {
	Config *config;
	GraphicBuffer *buffer;

	int cell_size;
	int shift_x, shift_y;

public:
	LifeCut();
	virtual ~LifeCut();

	virtual void setConfig(Config *_config) { config = _config; }
	virtual void setBuffer(GraphicBuffer *_buffer) { buffer = _buffer; }

	virtual void init(Config *_config = NULL, GraphicBuffer *_buffer = NULL);
	virtual void draw(int x, int y);
	virtual void finalize();
};
