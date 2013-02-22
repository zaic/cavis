#include "cutgrayscale.h"

CutGrayScale::CutGrayScale() {
}

CutGrayScale::~CutGrayScale() {

}

void CutGrayScale::init(Config *_config, GraphicBuffer *_buffer) {
	if(_config) config = _config;
	if(_buffer) buffer = _buffer;
}

void CutGrayScale::draw(int x, int y) {
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

void CutGrayScale::finalize() {

}
