#pragma once

#include "../common.h"
#include "../config/config.h"
#include "../buffer/buffer.h"
#include <QLayout>

class Renderer {
	Renderer(const Renderer& );
	Renderer& operator=(const Renderer& );

protected:
	Renderer();
	Config *config;
	GraphicBuffer *buffer;

public:
	virtual ~Renderer();

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
