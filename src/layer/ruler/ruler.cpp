#include "ruler.h"

RulerLayer::RulerLayer() :
    xstart(0),
    xstep(1),
    xframe(DEFAULT_FRAME_SIZE),
    ystart(0),
    ystep(1),
    yframe(DEFAULT_FRAME_SIZE)
{

}

RulerLayer::~RulerLayer()
{

}

void RulerLayer::drawX()
{
    painter->setPen(Qt::black);
    painter->drawLine(0, xframe, painter->window().width(), xframe);
    int count = divup(-xstart, xstep);
    xstart += count * xstep;
    int num_step = (xstep >= MIN_XSTEP ? 1 : divup(MIN_XSTEP, xstep));
    xstep *= num_step;
    for(int pos = xstart + yframe, num = count; pos <= painter->window().width(); pos += xstep, num += num_step)
        painter->drawText(pos, xframe - 10, QString("%1").arg(num));
}

void RulerLayer::drawY()
{
    painter->setPen(Qt::black);
    painter->drawLine(yframe, 0, yframe, painter->window().height());
    int count = divup(-ystart, ystep);
    ystart += count * ystep;
    int num_step = (ystep >= MIN_YSTEP ? 1 : divup(MIN_YSTEP, ystep));
    ystep *= num_step;
    for(int pos = ystart + xframe + 12, num = count; pos <= painter->window().height(); pos += ystep, num += num_step)
        painter->drawText(5, pos, QString("%1").arg(num));

}

void RulerLayer::draw()
{
    drawX();
    drawY();
}
