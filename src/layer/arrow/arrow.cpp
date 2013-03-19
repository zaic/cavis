#include "arrow.h"

ArrowLayer::ArrowLayer(int _len, int _end_len) : len(_len), end_len(_end_len)
{

}

ArrowLayer::~ArrowLayer()
{

}

void ArrowLayer::draw(int x, int y, uint mask, int mask_size, float start_angle, Direction dir)
{
    if(painter == NULL) {
        qWarning() << "[layer/arrow] painter is NULL";
        return ;
    }

    painter->setPen(color);
    const float angle_shift = 2.0 * M_PI / mask_size;
    const float angle_parts = M_PI * 3 / 4;

    for(int i = 0; i < mask_size; i++) {
        if(!(mask & (1<<i))) continue;

        float current_angle = start_angle + angle_shift * i * static_cast<int>(dir);
        int x_from = x;
        int y_from = y;

        // draw arrow
        int x_to = static_cast<int>(x_from + len * cos(current_angle) + .5);
        int y_to = static_cast<int>(y_from - len * sin(current_angle) + .5);
        painter->drawLine(x_from, y_from, x_to, y_to);

        // TODO improve quality
        // draw left part
        const float angle_left = current_angle + angle_parts;
        int xl_to = static_cast<int>(x_to + end_len * cos(angle_left) + .5);
        int yl_to = static_cast<int>(y_to - end_len * sin(angle_left) + .5);
        painter->drawLine(x_to, y_to, xl_to, yl_to);

        // draw right part
        const float angle_right = current_angle - angle_parts;
        int xr_to = static_cast<int>(x_to + end_len * cos(angle_right) + .5);
        int yr_to = static_cast<int>(y_to - end_len * sin(angle_right) + .5);
        painter->drawLine(x_to, y_to, xr_to, yr_to);
    }
}
