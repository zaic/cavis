#include "hpploupe.h"

HPPLoupeRenderer::HPPLoupeRenderer() : cell_size(0), shift_x(0), shift_y(0)
{
    arrow_layer.setArrowEndLength(3);
    arrow_layer.setColor(Qt::black);
}

HPPLoupeRenderer::~HPPLoupeRenderer()
{

}

void HPPLoupeRenderer::draw()
{
    /*
     *  Calc cell size
     */
    if(autoscale) {
        int cell_width  = (buffer->width() - 2) / config->getDimSizeX();
        int cell_height = (buffer->height() - 2) / config->getDimSizeY();
        cell_size = min(cell_width, cell_height);
        if(cell_size % 2 == 0) cell_size--;
    } else {
        cell_size = scale_cell_size * 2 + 1;
    }

    /*
     *  Prepare buffer and scrollbars
     */
    int buffer_x_have = buffer->width() - ruler_layer.getYFrame() - 1;
    int buffer_x_required = cell_size * config->getDimSizeX();
    if(buffer_x_required > buffer_x_have)
        buffer->setXScroll(divup(buffer_x_required - buffer_x_have, cell_size));
    else
        buffer->setXScroll(GraphicBuffer::SCROLL_DISABLE);

    int buffer_y_have = buffer->height() - ruler_layer.getXFrame() - 1;
    int buffer_y_required = cell_size * config->getDimSizeY();
    if(buffer_y_required > buffer_y_have)
        buffer->setYScroll(divup(buffer_y_required - buffer_y_have, cell_size));
    else
        buffer->setYScroll(GraphicBuffer::SCROLL_DISABLE);

    buffer->prepare();
    QPainter *painter = buffer->getRawPaintDevice();

    /*
     *  Prepare layers
     */
    ruler_layer.setPainter(painter);
    ruler_layer.setXStart(cell_size / 3 - cell_size * buffer->getXScroll()); // TODO: add align to ruler?
    ruler_layer.setXStep(cell_size);
    ruler_layer.setYStart(cell_size / 3 - cell_size * buffer->getYScroll());
    ruler_layer.setYStep(cell_size);
    shift_x = ruler_layer.getXFrame() + 1 - buffer->getXScroll() * cell_size;
    shift_y = ruler_layer.getYFrame() + 1 - buffer->getYScroll() * cell_size;
    qDebug() << "[render/hpp] shift:" << shift_x << shift_y;

    arrow_layer.setPainter(painter);
    arrow_layer.setArrowLength(cell_size / 2 - 1);
    arrow_layer.setArrowEndLength(max(2, cell_size / 13));
    for(int y = 0; y < config->getDimSizeY(); y++) {
        for(int x = 0; x < config->getDimSizeX(); x++) {
            // тут за нами полный выбор где рисовать
            uchar* data = reinterpret_cast<uchar*>(config->getData());
            const int rx = config->getDimSizeX();
            int id = (y * rx + x);
            uchar cell_data = data[id];
            uint value = 0xffeeeeee;

            // TODO draw lightgray rectangle

            painter->fillRect(shift_x + x * cell_size, shift_y + y * cell_size, cell_size - 1, cell_size - 1, QColor(value));

            const int cell_mid_x = shift_x + x * cell_size + cell_size / 2 + 1;
            const int cell_mid_y = shift_y + y * cell_size + cell_size / 2 + 1;
            arrow_layer.draw(cell_mid_x, cell_mid_y, cell_data, 4, M_PI / 2.0);
        }
    }

    painter->fillRect(0, 0, buffer->width(), ruler_layer.getXFrame(), Qt::white);
    painter->fillRect(0, 0, ruler_layer.getYFrame(), buffer->height(), Qt::white);
    ruler_layer.draw();
}
