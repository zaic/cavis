#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#undef _USE_MATH_DEFINES
#include "layer/layer.h"
#include <QDebug>

class ArrowLayer : public Layer
{
    int len;
    int end_len;
    QColor color;

public:
    ArrowLayer(int _len = 5, int _end_len = 3);
    virtual ~ArrowLayer();

    void setArrowLength(int _len) { len = _len; }
    void setArrowEndLength(int _end_len) { end_len = _end_len; }
    void setColor(const QColor& _color) { color = _color; }

    enum Direction { CLOCKWISE = -1, COUNTERCLOCKWISE = 1 };
    void draw(int x, int y, uint mask, int mask_size, float start_angle = 0.0, Direction dir = CLOCKWISE);
};
