#pragma once

#include "../common.h"

class GraphicBuffer {
	GraphicBuffer(const GraphicBuffer& );
	GraphicBuffer& operator=(const GraphicBuffer& );

protected:
	GraphicBuffer();

public:
	virtual ~GraphicBuffer();

	virtual bool prepare(int real_width = -1, int real_height = -1, int shift_x = -1, int shift_y = -1) = 0;
	virtual void complete() = 0;

	virtual int width() const = 0;
	virtual int height() const = 0;

	virtual void setColor(uint color) = 0;

	virtual void drawPixel(int x, int y) = 0;
};
