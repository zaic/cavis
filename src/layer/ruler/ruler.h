#pragma once

#include "layer/layer.h"
#include "common.h"
#include <QtGui>

class RulerLayer : public Layer
{
    int xstart, xstep, xframe;
    int ystart, ystep, yframe;

    static const int DEFAULT_FRAME_SIZE = 25;
    const int MIN_XSTEP = 20;
    const int MIN_YSTEP = 10;

public:
    RulerLayer();
    virtual ~RulerLayer();

    // TODO: add const CV
    void setXStart(int val) { xstart = val; }
    void setXStep (int val) { xstep  = val; }
    void setXFrame(int val) { xframe = (val >= 10 ? val : 10); }
    void setYStart(int val) { ystart = val; }
    void setYStep (int val) { ystep  = val; }
    void setYFrame(int val) { yframe = (val >= 10 ? val : 10); }

    int getXFrame() const { return xframe; }
    int getYFrame() const { return yframe; }

    void drawX();
    void drawY();
    void draw();
};
