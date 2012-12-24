#pragma once

#include "../common.h"

class GraphicBuffer {
	GraphicBuffer(const GraphicBuffer& );
	GraphicBuffer& operator=(const GraphicBuffer& );

protected:
	GraphicBuffer();

public:
	virtual ~GraphicBuffer();

	virtual int getX() const = 0;
	virtual int getY() const = 0;

	virtual void setColor(uint color) = 0;

	virtual void drawPixel(int x, int y) = 0;
};
