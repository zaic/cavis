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
	int buffer_using_width = min(config->getRealDimSizeX(), buffer->width());
	int shift_x = 0;
	if(buffer_using_width < buffer->width()) {
		shift_x = (buffer->width() - buffer_using_width) / 2;
	}
	qDebug() << "[render/proj] start drawing...";

	// preparing data for interpolation
	const int n = config->getRealDimSizeX();
	const double* data = reinterpret_cast<const double*>(config->getRealData());

	vector<double> data_x, data_y;
	double max_value = data[0], min_value = data[0];
	const double x_scaled = (n - 1) / 100.0 * parameters->x_scale->value();
	for(int i = 0; i < n; i++) {
		double x = i * (parameters->x_scale->value() / 100.0);
		//qDebug() << x << ":" << data[i];
		data_x.push_back(x);
		data_y.push_back(data[i] * parameters->y_scale->value());
		max_value = max(max_value, data[i]);
		min_value = min(min_value, data[i]);
	}

	// interpolation
	Interpolator inter(data_x, data_y);
	const int nn = int(x_scaled);
	int last_value = -1;

	buffer->prepare(nn, int(min_value + max_value) + 1, -50, 0);
	// Draw grid
	const int frame_size = 50;
	const int value_invert = buffer->height() - frame_size;
	for(int i = 0; i <= buffer->height() / parameters->y_scale->value(); i++) {
		int x = buffer->getX(frame_size);
		int y = value_invert - i * parameters->y_scale->value();
		// primary dark grid
		buffer->setColor(0xffaaaaaa);
		buffer->drawLine(x, y, buffer->getX(buffer->width()), y);
		buffer->setColor(0xff000000);
		buffer->drawText(x - frame_size * 4 / 5, y, toStdString<int>(i).c_str());
		// secondary light grid
		const int cnt = parameters->y_scale->value() / 25;
		const int secondary_height = parameters->y_scale->value() / cnt;
		for(int j = 1; j < cnt; j++) {
			buffer->setColor(0xffdddddd);
			y -= secondary_height;
			buffer->drawLine(x, y, buffer->getX(buffer->width()), y);
			buffer->setColor(0xff555555);
			buffer->drawText(x - frame_size * 4 / 5, y, toStdString<double>(i + 1.0 / (cnt + 1) * (j)).substr(0, 4).c_str());
		}
	}
	for(int i = 0; i <= buffer->width(); i++) {
		//int x = buffer->getX(frame_size + )
	}
	uint color = 0xffff0000;
	buffer->setColor(color);

	for(int x = 0; x < nn; x++) {
		const int rx = x; //config->getRealDimSizeX();
		int value = int(inter.Eval(x) + .5);
		//qDebug() << "value on x" << x << "is" << value;
		value = value_invert - value;
		if(last_value != -1)
			buffer->drawLine(x - 1, last_value, x, value);
		else
			buffer->drawPixel(rx, value);
		last_value = value;
	}
	// TODO: draw numbers
}
