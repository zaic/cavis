#include "grayscale.h"
#include <cstdint>

GrayScaleRenderer::GrayScaleRenderer()
{

}

GrayScaleRenderer::~GrayScaleRenderer()
{

}

void GrayScaleRenderer::prepare()
{

}

void GrayScaleRenderer::draw(void *_device)
{
    const int cell_size = 1;
    buffer->prepare();
    QPainter *painter = buffer->getRawPaintDevice();

    uint8_t* data = reinterpret_cast<uint8_t*>(config->getData());
    const int rx = config->getDimSizeX();

    //qDebug() << "[render/gray] y =" << config->getDimSizeY() << "x =" << config->getDimSizeX();

    for(int y = 0; y < config->getDimSizeY(); y++)
        for(int x = 0; x < config->getDimSizeX(); x++) {
            int id = (y * rx + x);
            uint8_t cell_data = data[id];
            //qDebug() << "[render/gray] rx" << rx << "x" << x << "y" << y << "id" << id;
            //qDebug() << "[render/gray] value at" << id << "=" << cell_data;
            //int bits = __builtin_popcount(cell_data);
            //int bits = cell_data;
            //uint value = 0xffeeeeee - 0x010101 * bits; // TODO fix color convert ?
            uint8_t value = cell_data; // TODO fix color convert ?
            int shift_x = 0, shift_y = 0;

            QColor cell_color(value & 0xFF, value & 0xFF, value & 0xFF);
            painter->fillRect(shift_x + x * cell_size, shift_y + y * cell_size, cell_size, cell_size, cell_color);
        }
}
