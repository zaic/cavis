#include "grayscale.h"

GrayScaleRenderer::GrayScaleRenderer() {
}

GrayScaleRenderer::~GrayScaleRenderer() {

}

void GrayScaleRenderer::draw() {
#if 0
	for(int y = 0; y < config->getRealDimSizeY(); y++)
		for(int x = 0; x < config->getRealDimSizeX(); x++) {
			renderer->draw(x, y);
		}
#endif
	for(int y = 0; y < config->getRealDimSizeY(); y++)
		for(int x = 0; x < config->getRealDimSizeX(); x++) {
			uchar* data = (uchar*)config->getRealData();
			const int rx = config->getRealDimSizeX();
			int id = (y * rx + x);
			uchar cell_data = data[id];
			int bits = __builtin_popcount(cell_data);
			uint value = 0xffeeeeee - 0x333333 * bits;
			int cell_size = 15;
			int shift_x = 0, shift_y = 0;

			buffer->setColor(value);
			for(int i = 0; i < cell_size; i++)
				for(int j = 0; j < cell_size; j++)
					buffer->drawPixel(shift_x + x * cell_size + i, shift_y + y * cell_size + j);
		}
}
