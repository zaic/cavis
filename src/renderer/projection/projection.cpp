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
	int buffer_using_width = min(config->getRealDimSizeX(), buffer->width());
	int shift_x = 0;
	if(buffer_using_width < buffer->width()) {
		shift_x = (buffer->width() - buffer_using_width) / 2;
	}
	buffer->prepare(config->getRealDimSizeX(), 10, -shift_x, 0);

	qDebug() << "[render/proj] start drawing...";



	// preparing data for interpolation
	const int n = config->getRealDimSizeX();
	const double* data = reinterpret_cast<const double*>(config->getRealData());

	vector<double> data_x, data_y;
	double max_value = data[0];
	const double x_scaled = (n - 1) / 100.0 * parameters->scale->value();
	for(int i = 0; i < n; i++) {
		double x = i * (parameters->scale->value() / 100.0);
		//qDebug() << x << ":" << data[i];
		data_x.push_back(x);
		data_y.push_back(data[i] * parameters->factor->value());
		max_value = max(max_value, data[i]);
	}

	// interpolation
	Interpolator inter(data_x, data_y);
	const int nn = int(x_scaled);
	const int value_invert = buffer->height() - 100;
	int last_value = -1;

	// TODO: move buffer->prepare && draw grid
	buffer->setColor(0xffcccccc);
	for(int i = 0; i < 5; i++)
		buffer->drawLine(0, value_invert - i * parameters->factor->value(), nn, value_invert - i * parameters->factor->value());
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
