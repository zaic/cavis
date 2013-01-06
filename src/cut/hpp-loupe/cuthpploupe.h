#pragma once

#include "../cut.h"
#include "../../common.h"
#include "../../config/config.h"
#include <algorithm>
#include <QDebug>

using std::min;

class CutHPPLoupe : public Cut {
	int cell_size;
	int shift_x, shift_y;

public:
	CutHPPLoupe();
	virtual ~CutHPPLoupe();

	virtual void init(Config *_config = NULL, GraphicBuffer *_buffer = NULL);
	virtual void draw(int x, int y);
	virtual void finalize();
};
