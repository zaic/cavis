#include "grayscale.h"

GrayScaleRenderer::GrayScaleRenderer()
{

}

GrayScaleRenderer::~GrayScaleRenderer()
{

}

void GrayScaleRenderer::draw()
{
#if 0
	for(int y = 0; y < config->getRealDimSizeY(); y++)
		for(int x = 0; x < config->getRealDimSizeX(); x++) {
			renderer->draw(x, y);
		}
#endif
	const int cell_size = 15;
	buffer->prepare(cell_size * config->getDimSizeX(), cell_size * config->getDimSizeY());
	for(int y = 0; y < config->getDimSizeY(); y++)
		for(int x = 0; x < config->getDimSizeX(); x++) {
			uchar* data = reinterpret_cast<uchar*>(config->getData());
			const int rx = config->getDimSizeX();
			int id = (y * rx + x);
			uchar cell_data = data[id];
			int bits = __builtin_popcount(cell_data);
			uint value = 0xffeeeeee - 0x333333 * bits;
			int shift_x = 0, shift_y = 0;

			buffer->setColor(value);
			for(int i = 0; i < cell_size; i++)
				for(int j = 0; j < cell_size; j++)
					buffer->drawPixel(shift_x + x * cell_size + i, shift_y + y * cell_size + j);
		}
}
