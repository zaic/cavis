/*
 *	2D_Real => 2D_Logic
 */

#pragma once

#include "../common.h"
#include "../config/config.h"
#include "../buffer/buffer.h"

class Cut2D {
	Cut2D(const Cut2D& );
	Cut2D& operator=(const Cut2D& );

public:
	Cut2D();
	virtual ~Cut2D();

	// нужны ли? если да, возможно, занести в protected
	virtual void setConfig(Config *config) = 0;
	virtual void setBuffer(GraphicBuffer *buffer) = 0;

	// call before each iteration
	virtual void init(Config *config = NULL, GraphicBuffer *buffer = NULL) = 0;
	// call on each cell
	virtual void draw(int x, int y) = 0;
	// call after each iteration
	virtual void finalize() = 0;
};
