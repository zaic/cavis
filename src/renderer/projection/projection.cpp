#include "projection.h"

ProjectionRenderer::ProjectionRenderer()
{

}

ProjectionRenderer::~ProjectionRenderer()
{

}

void ProjectionRenderer::init(Config *_config, GraphicBuffer *_buffer)
{
	qDebug() << "[render/proj] start!";
	if(_config) config = _config;
	if(_buffer) buffer = _buffer;
	last_value = -101.0;
	buffer_using_width = min(config->getRealDimSizeX(), buffer->width());
	int shift_x = 0;
	if(buffer_using_width < buffer->width()) {
		shift_x = (buffer->width() - buffer_using_width) / 2;
	}
	buffer->prepare(config->getRealDimSizeX(), 10, -shift_x, 0);
}

void ProjectionRenderer::draw(int x, int y)
{
	qDebug() << "[render/proj] x = " << x << ", y = " << y;
	if(y != 1) y = 1;
	const double* data = reinterpret_cast<const double*>(config->getRealData());
	const int rx = x; //config->getRealDimSizeX();
	int value = int(data[rx] * 100 + .5);
	uint color = 0xffff0000;

	buffer->setColor(color);
	buffer->drawPixel(rx, 400 - value);
	buffer->setColor(0xff000000);
	buffer->drawPixel(rx, 400);
}

void ProjectionRenderer::finalize()
{

}
