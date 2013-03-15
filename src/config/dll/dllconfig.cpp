#include "dllconfig.h"

DLLConfig::DLLConfig()
{
    // TODO
}

DLLConfig::~DLLConfig()
{
    // TODO
}

int DLLConfig::getDimSize(int dim) const {
    if(dim == 0) return size_x;
    if(dim == 1) return size_y;
    return 1;
}

int DLLConfig::setFrame(int frame) {
    if(frame < current_frame_id || frame > current_frame_id + 1) return Config::FRAME_NOT_CHANGED;
    if(frame == current_frame_id + 1) {
        // TODO: load
        current_frame_id = frame;
    }
    return current_frame_id;
}
