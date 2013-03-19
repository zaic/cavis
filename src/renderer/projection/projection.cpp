#include "projection.h"

ProjectionRenderer::ProjectionRenderer()
{
    parameters = NULL;
}

ProjectionRenderer::~ProjectionRenderer()
{

}

void ProjectionRenderer::draw()
{
    qDebug() << "[render/proj] start!";

    // preparing data for interpolation
    const int n = config->getDimSizeX();
    const double* data = reinterpret_cast<const double*>(config->getData());

    vector<double> data_x, data_y;
    double max_value = data[0], min_value = data[0];
    const double x_scaled = (n - 1) / 100.0 * parameters->x_scale->value();
    for(int i = 0; i < n; i++) {
        double x = i * (parameters->x_scale->value() / 100.0);
        data_x.push_back(x);
        data_y.push_back(data[i] * parameters->y_scale->value());
        max_value = max(max_value, data[i]);
        min_value = min(min_value, data[i]);
    }

    if(config->getDimSizeX() == 0) {
        buffer->prepare();
        return ;
    }

    // interpolation
    Interpolator inter(data_x, data_y);
    const int nn = int(x_scaled);

    qDebug() << "xscal" << x_scaled << "buf->width" << buffer->width();
    if(buffer->width() - 50 < x_scaled)
        buffer->setXScroll(divup<int>(x_scaled - buffer->width() - 50, 100));
    else
        buffer->setXScroll(GraphicBuffer::SCROLL_DISABLE);
    // TODO y-scroll
    // TODO more nice view
    // TODO 100 should be constant
    buffer->prepare();
    QPainter *painter = buffer->getRawPaintDevice();

    /*
     * Draw grid
     */
    const int shift_x = FRAME_SIZE - buffer->getXScroll() * 100;
    const int value_invert = buffer->height() - FRAME_SIZE;

    QPicture digits_picuture;
    QPainter digits_painter(&digits_picuture);

    // y-axis
    digits_painter.fillRect(0, 0, FRAME_SIZE, buffer->height(), Qt::white);
    for(int i = 0; i <= buffer->height() / parameters->y_scale->value(); i++) {
        int x = FRAME_SIZE;
        int y = value_invert - i * parameters->y_scale->value();

        // primary dark grid
        painter->setPen(QColor(0xAA, 0xAA, 0xAA));
        painter->drawLine(x, y, buffer->width(), y);
        digits_painter.setPen(Qt::black);
        digits_painter.drawText(x - FRAME_SIZE * 4 / 5, y, toStdString<int>(i).c_str());

        // secondary light grid
        const int cnt = parameters->y_scale->value() / 25;
        const int secondary_height = parameters->y_scale->value() / cnt;
        painter->setPen(QColor(0xDD, 0xDD, 0xDD));
        digits_painter.setPen(QColor(0x55, 0x55, 0x55));
        for(int j = 1; j < cnt; j++) {
            y -= secondary_height;
            painter->drawLine(x, y, buffer->width(), y);
            digits_painter.drawText(x - FRAME_SIZE * 4 / 5, y, toStdString<double>(i + 1.0 / (cnt + 1) * (j)).substr(0, 4).c_str());
        }
    }

    // x-axis
    digits_painter.begin(&digits_picuture);
    digits_painter.fillRect(0, 0, buffer->width(), FRAME_SIZE, Qt::white);
    for(int i = 0; i <= buffer->width() / parameters->x_scale->value(); i++) {
        int x = FRAME_SIZE + i * parameters->x_scale->value();
        int y = value_invert;

        // primary dark grid
        painter->setPen(QColor(0xAA, 0xAA, 0xAA));
        painter->drawLine(x, y, x, 0);
        digits_painter.setPen(Qt::black);
        digits_painter.drawText(x, y + FRAME_SIZE / 2, toStdString<int>(i * 100 + buffer->getXScroll() * 100).c_str());
    }
    // TODO: draw numbers

    digits_painter.end();

    /*
     *  Draw interpolation values
     */
    if(parameters->chk_interpolation->isChecked()) {
        painter->setPen(QColor(0xCC, 0x00, 0x00));
        int last_value = -1;
        for(int x = 0; x < nn; x++) {
            int value = int(inter.Eval(x) + .5);
            value = value_invert - value;
            if(last_value != -1)
                painter->drawLine(x - 1 + shift_x, last_value, x + shift_x, value);
            else
                painter->drawPoint(x + shift_x, value);
            last_value = value;
        }
    }

    /*
     *  Draw given value
     */
    if(parameters->chk_segments->isChecked()) {
        painter->setPen(QColor(0x00, 0xCC, 0x00));
        int px = data_x[0];
        int py = data_y[0];
        for(int ii = 1; ii < n / 10; ii++) {
            int i = ii * 10;
            painter->drawLine(px + shift_x, value_invert - py, data_x[i] + shift_x, value_invert - data_y[i]);
            px = data_x[i];
            py = data_y[i];
        }
    }

    painter->drawPicture(0, 0, digits_picuture);
}
