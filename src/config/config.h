#pragma once

#include <cstddef>

// TODO: add some factory for creating needed ConfigClass for opened model?

class Config
{
    Config(const Config& );
    Config& operator=(const Config& );

protected:
    int current_frame_id;

    Config();

public:
    virtual ~Config();

    static const int FRAME_NOT_CHANGED = -1807; // TODO remove
    static const int FRAME_FORCED_UPDATE = -3004;

    virtual int prevFrame() { return setFrame(current_frame_id - 1); }
    virtual int nextFrame() { return setFrame(current_frame_id + 1); }
    virtual int setFrame(int) { return FRAME_NOT_CHANGED; }
    virtual int getFramesCount() { return 0; }

    virtual void* getData(void* data_type = NULL) = 0;
    virtual int getDimSize(int dim) const = 0;
    virtual int getDimSizeX() const { return getDimSize(0); }
    virtual int getDimSizeY() const { return getDimSize(1); }
    virtual int getDimSizeZ() const { return getDimSize(2); }
};
