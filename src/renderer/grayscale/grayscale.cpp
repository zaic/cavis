#include "grayscale.h"

GrayScaleRenderer::GrayScaleRenderer()
{

}

GrayScaleRenderer::~GrayScaleRenderer()
{

}

void GrayScaleRenderer::draw()
{
    const int cell_size = 2;
    buffer->prepare(cell_size * config->getDimSizeX(), cell_size * config->getDimSizeY());
    QPainter *painter = buffer->getRawPaintDevice();
    for(int y = 0; y < config->getDimSizeY(); y++)
        for(int x = 0; x < config->getDimSizeX(); x++) {
            uchar* data = reinterpret_cast<uchar*>(config->getData());
            const int rx = config->getDimSizeX();
            int id = (y * rx + x);
            uchar cell_data = data[id];
            int bits = __builtin_popcount(cell_data);
            uint value = 0xffeeeeee - 0x333333 * bits; // TODO fix color convert ?
            int shift_x = 0, shift_y = 0;

            painter->setPen(QColor(value & 0xFF, value & 0xFF, value & 0xFF));
            for(int i = 0; i < cell_size; i++)
                for(int j = 0; j < cell_size; j++)
                    painter->drawPoint(shift_x + x * cell_size + i, shift_y + y * cell_size + j);
        }
}
