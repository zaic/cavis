#include "hpploupe.h"

HPPLoupeRenderer::HPPLoupeRenderer() : cell_size(0), shift_x(0), shift_y(0)
{

}

HPPLoupeRenderer::~HPPLoupeRenderer()
{

}

void HPPLoupeRenderer::draw()
{
    if(autoscale) {
        int cell_width  = (buffer->width() - 2) / config->getDimSizeX();
        int cell_height = (buffer->height() - 2) / config->getDimSizeY();
        cell_size = min(cell_width, cell_height);
        if(cell_size % 2 == 0) cell_size--;
    } else {
        cell_size = scale_cell_size * 2 + 1;
    }

    shift_x = (buffer->width() - 2 - cell_size * config->getDimSizeX()) / 2;
    shift_y = (buffer->height() - 2 - cell_size * config->getDimSizeY()) / 2;
    // TODO: move to buffer
    shift_x = shift_y = 0;

    buffer->prepare(cell_size * config->getDimSizeX(), cell_size * config->getDimSizeY());
    QPainter *painter = buffer->getRawPaintDevice();

    for(int y = 0; y < config->getDimSizeY(); y++) {
        for(int x = 0; x < config->getDimSizeX(); x++) {
            // тут за нами полный выбор где рисовать
            uchar* data = reinterpret_cast<uchar*>(config->getData());
            const int rx = config->getDimSizeX();
            int id = (y * rx + x);
            uchar cell_data = data[id];
            uint value = 0xffeeeeee;

            // TODO replace to fillRectangle
            // TODO draw lightgray rectangle

            painter->setPen(value);
            for(int i = 1; i < cell_size; i++)
                for(int j = 1; j < cell_size; j++)
                    painter->drawPoint(shift_x + x * cell_size + i, shift_y + y * cell_size + j);

            const int dim[4][2] = { {0, -1}, {1, 0}, {0, 1}, {-1, 0} };
            const int cell_mid_x = shift_x + x * cell_size + cell_size / 2 + 1;
            const int cell_mid_y = shift_y + y * cell_size + cell_size / 2 + 1;
            painter->setPen(Qt::black);
            for(int i = 0; i < 4; i++)
                if(cell_data & (1 << i)) {
                    for(int k = 0; k <= cell_size / 2; k++)
                        painter->drawPoint(cell_mid_x + k * dim[i][0], cell_mid_y + k * dim[i][1]);
                    for(int k = 0; k < 4; k++) {
                        for(int q = 1; q < 2; q++)
                            painter->drawPoint(cell_mid_x + (cell_size / 2 - q) * dim[i][0] + dim[k][0] * q, cell_mid_y + (cell_size / 2 - q) * dim[i][1] + dim[k][1] * q);
                    }
                }
        }
    }
}
