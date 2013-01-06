/*
 *	2D_Real => 2D_Logic
 */

// TODO: rename to Map

#pragma once

#include "../common.h"
#include "../config/config.h"
#include "../buffer/buffer.h"
#include <QLayout>

class Cut {
	Cut(const Cut& );
	Cut& operator=(const Cut& );

protected:
	Config *config;
	GraphicBuffer *buffer;

public:
	Cut();
	virtual ~Cut();

	virtual void setConfig(Config *_config) { config = _config; }
	virtual void setBuffer(GraphicBuffer *_buffer) { buffer = _buffer; }
	virtual Config* getConfig() const { return config; }
	virtual GraphicBuffer* getBuffer() const { return buffer; }

	// call before each iteration
	virtual void init(Config *config = NULL, GraphicBuffer *buffer = NULL) = 0;
	// call on each cell
	virtual void draw(int x, int y) = 0;
	// call after each iteration
	virtual void finalize() = 0;
};
