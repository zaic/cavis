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
    DLLConfig();
    virtual ~DLLConfig();

    virtual int setFrame(int frame);
    virtual int getFramesCount() { return current_frame_id; }

    virtual const char* getRealData() const { return NULL; }
    virtual int getRealDimSize(int dim) const;
    virtual int getRealDimSizeX() const { return size_x; }
    virtual int getRealDimSizeY() const { return size_y; }
    virtual int getRealDimSizeZ() const { return 1; }
};
