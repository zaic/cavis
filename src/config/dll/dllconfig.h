#pragma once

#include <cstdlib>
#include "../config.h"
//#include "../../libca/src/hpp.h"

class DLLConfig : public Config
{
    DLLConfig(const DLLConfig& );
    DLLConfig& operator=(const DLLConfig& );

    int size_x, size_y;

public:
    DLLConfig(const char *path);
    virtual ~DLLConfig();

    virtual int setFrame(int frame);
    virtual int getFramesCount() { return current_frame_id; }

	virtual void* getData(void* = NULL) { return NULL; }
    virtual int getDimSize(int dim) const;
    virtual int getDimSizeX() const { return size_x; }
    virtual int getDimSizeY() const { return size_y; }
    virtual int getDimSizeZ() const { return 1; }
};
