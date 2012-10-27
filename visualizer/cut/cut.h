/*
 *	2D_Real => 2D_Logic
 */

#pragma once

#include "../common.h"
#include "../config/config.h"

class Cut2D {
	Cut2D(const Cut2D& );
	Cut2D& operator=(const Cut2D& );

public:
	Cut2D();
	virtual ~Cut2D();

	virtual void operator()(int x, int y, Config *config, void *result) = 0;
};
