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
    // TODO: remove ?
#if 0
    int buffer_using_width = min(config->getRealDimSizeX(), buffer->width());
    int shift_x = 0;
    if(buffer_using_width < buffer->width()) {
        shift_x = (buffer->width() - buffer_using_width) / 2;
    }
#endif
    qDebug() << "[render/proj] start drawing...";

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

    // interpolation
    Interpolator inter(data_x, data_y);
    const int nn = int(x_scaled);
    int last_value = -1;

    qDebug() << "xscal" << x_scaled << "buf->width" << buffer->width();
    if(buffer->width() - 50 < x_scaled)
        buffer->setXScroll(divup<int>(x_scaled - buffer->width() - 50, 100));
    else
        buffer->setXScroll(GraphicBuffer::SCROLL_DISABLE);
    // TODO y-scroll
    // TODO more nice view
    // TODO 100 should be constant
    buffer->prepare(nn, int(min_value + max_value) + 1, -50, 0);
    QPainter *painter = buffer->getRawPaintDevice();

    /*
     * Draw grid
     */
    const int frame_size = 50;
    const int shift_x = frame_size - buffer->getXScroll() * 100;
    const int value_invert = buffer->height() - frame_size;

    QPicture digits_picuture;
    QPainter digits_painter;
    digits_painter.begin(&digits_picuture);
    digits_painter.fillRect(0, 0, frame_size, buffer->height(), Qt::white);
    for(int i = 0; i <= buffer->height() / parameters->y_scale->value(); i++) { // TODO: fix? y_scale in per cents
        int x = frame_size;
        int y = value_invert - i * parameters->y_scale->value();
        // primary dark grid
        digits_painter.setPen(QColor(0xAA, 0xAA, 0xAA));
        digits_painter.drawLine(x, y, buffer->width(), y);
        digits_painter.setPen(Qt::black);
        digits_painter.drawText(x - frame_size * 4 / 5, y, toStdString<int>(i).c_str());
        // secondary light grid
        const int cnt = parameters->y_scale->value() / 25;
        const int secondary_height = parameters->y_scale->value() / cnt;
        for(int j = 1; j < cnt; j++) {
            y -= secondary_height;
            digits_painter.setPen(QColor(0xDD, 0xDD, 0xDD));
            digits_painter.drawLine(x, y, buffer->width(), y);
            digits_painter.setPen(QColor(0x55, 0x55, 0x55));
            digits_painter.drawText(x - frame_size * 4 / 5, y, toStdString<double>(i + 1.0 / (cnt + 1) * (j)).substr(0, 4).c_str());
        }
    }
    digits_painter.end();
    painter->drawPicture(0, 0, digits_picuture);

    /*
     *  Draw interpolation values
     */
    if(parameters->chk_interpolation->isChecked()) {
        painter->setPen(QColor(0xCC, 0x00, 0x00));
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

    // TODO: draw numbers
}
