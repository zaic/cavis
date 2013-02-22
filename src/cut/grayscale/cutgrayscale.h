#pragma once

#include "../cut.h"
#include "../../common.h"
#include "../../config/config.h"
#include <algorithm>
#include <QDebug>

class CutGrayScale : public Cut
{
	CutGrayScale(const CutGrayScale& );
	CutGrayScale& operator=(const CutGrayScale& );

public:
	CutGrayScale();
	virtual ~CutGrayScale();

	virtual void init(Config *_config = NULL, GraphicBuffer *_buffer = NULL);
	virtual void draw(int x, int y);
	virtual void finalize();
};
