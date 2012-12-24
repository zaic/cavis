#include "lifecut.h"

LifeCut::LifeCut() : config(NULL), buffer(NULL), cell_size(0), shift_x(0), shift_y(0) {

}

LifeCut::~LifeCut() {

}

void LifeCut::init(Config *_config, GraphicBuffer *_buffer) {
	if(_config) config = _config;
	if(_buffer) buffer = _buffer;

	int cell_width  = (buffer->getX() - 2) / config->getRealDimSizeX();
	int cell_height = (buffer->getY() - 2) / config->getRealDimSizeY();
	cell_size = min(cell_width, cell_height);

	shift_x = (buffer->getX() - 2 - cell_size * config->getRealDimSizeX()) / 2;
	shift_y = (buffer->getY() - 2 - cell_size * config->getRealDimSizeY()) / 2;
}

void LifeCut::draw(int x, int y) {
	// тут за нами полный выбор где рисовать
	uchar* data = (uchar*)config->getRealData();
	const int rx = config->getRealDimSizeX();
	int id = (y * rx + x);
	uint value = (data[id] ? 0xffeeeeee : 0x111111);
	qDebug() << "(" << x << ", " << y << ") " << value;
	//uint color = r  | (g << 8) | (b << 16) | 0xff000000;

	// TODO replace to fillRectangle
	// TODO draw lightgray rectangle
	buffer->setColor(value);
	for(int i = 1; i < cell_size; i++)
		for(int j = 1; j < cell_size; j++)
			buffer->drawPixel(shift_x + x * cell_size + i, shift_y + y * cell_size + j);
}

void LifeCut::finalize() {
	qDebug() << "sx = " << shift_x;
	qDebug() << "sy = " << shift_y;
	qDebug() << "cell_size = " << cell_size;
	// do nothing
}
