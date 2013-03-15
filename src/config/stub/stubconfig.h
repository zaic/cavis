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

	virtual void* getData(void* = NULL) { return real_data; }
	virtual int getDimSize(int dim) const;
	virtual int getDimSizeX() const { return real_x; }
	virtual int getDimSizeY() const { return real_y; }
	virtual int getDimSizeZ() const { return 1; }
};
