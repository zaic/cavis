#pragma once

#include <cstdlib>
#include "../config.h"
#include "../../common.h"
#include <dlfcn.h>

class DLLConfig : public Config
{
    DLLConfig(const DLLConfig& );
    DLLConfig& operator=(const DLLConfig& );

    /*
     *  DLL data
     */
    void *lib_handle;
    void (*lib_calc)();
    void* (*lib_data)();
    /*
     *  Model data
     */
    void *data;
    int size_x, size_y;

public:
    DLLConfig(const char *path);
    virtual ~DLLConfig();

    virtual int setFrame(int frame);
    virtual int getFramesCount() { return current_frame_id; }

    virtual void* getData(void* = NULL) { return data; }
    virtual int getDimSize(int dim) const;
    virtual int getDimSizeX() const { return size_x; }
    virtual int getDimSizeY() const { return size_y; }
    virtual int getDimSizeZ() const { return 1; }
};
