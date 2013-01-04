#pragma once

#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cassert>
#include <cstdlib>
#include "../config.h"

using std::ifstream;
using std::cerr;
using std::endl;
using std::stringstream;
using std::string;

class FileBasedConfig : public Config {
	FileBasedConfig();
	FileBasedConfig(const FileBasedConfig& );
	FileBasedConfig& operator=(const FileBasedConfig& );

	int real_x, real_y, element_size;
	int logic_x, logic_y;

	int frames_count;

	int current_frame;
	char* data;

public:
	FileBasedConfig(const char *filename, int x = 0, int y = 0);
	virtual ~FileBasedConfig();

	virtual bool prev();
	virtual bool next();
	virtual bool setFrame(int frame);
	virtual int getFramesCount() const { return frames_count; }

    virtual const char* getRealData() const { return data; }
	virtual int getRealDimSize(int dim) const;
	virtual int getRealDimSizeX() const { return real_x; }
	virtual int getRealDimSizeY() const { return real_y; }
	virtual int getRealDimSizeZ() const { return 1; }

	virtual void setLogicSize(int x, int y) { logic_x = x; logic_y = y; }
};
