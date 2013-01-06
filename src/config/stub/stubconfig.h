#pragma once

#include "../config.h"
#include <cstring>
#include <QDebug>

class StubConfig : public Config {
	int real_x, real_y;
	char *real_data;

protected:
	StubConfig();

public:
	StubConfig(int x, int y);
	virtual ~StubConfig();

	virtual int setFrame(int frame);
	virtual int getFramesCount() { return real_y - 2; }

	virtual const char* getRealData() const { return real_data; }
	virtual int getRealDimSize(int dim) const;
	virtual int getRealDimSizeX() const { return real_x; }
	virtual int getRealDimSizeY() const { return real_y; }
	virtual int getRealDimSizeZ() const { return 1; }
};
