#pragma once

#include "../cut.h"
#include "../../common.h"
#include "../../config/config.h"

class LifeCut : public Cut2D {
public:
	LifeCut();
	virtual ~LifeCut();

	virtual void operator()(int x, int y, Config *config, void *result);
};
