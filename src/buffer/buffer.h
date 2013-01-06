#pragma once

#include "../common.h"

class GraphicBuffer {
	GraphicBuffer(const GraphicBuffer& );
	GraphicBuffer& operator=(const GraphicBuffer& );

protected:
	GraphicBuffer();

public:
	virtual ~GraphicBuffer();

	virtual bool prepare() = 0;
	virtual void complete() = 0;

	virtual int width() const = 0;
	virtual int height() const = 0;

	virtual void setColor(uint color) = 0;

	virtual void drawPixel(int x, int y) = 0;
};
