#include "visualizzzator.h"

Visualizzzator::Visualizzzator(Config *_config, Cut2D *_cut) :
	config(_config),
	cut(_cut)
{

}

Visualizzzator::~Visualizzzator() {

}

void Visualizzzator::operator()(GraphicBuffer& buffer) {
	// TODO бегать нужно по логическому дву(трёх-)мерному пространству же!
	//     а пока что работает в предположении прямого отображения
	/*
	for(int y = 0; y < buffer.getY(); y++)
		for(int x = 0; x < buffer.getX(); x++) {
	*/
	for(int y = 0; y < config->getRealDimSize(0); y++)
		for(int x = 0; x < config->getRealDimSize(1); x++) {
			uint color;
			cut->operator()(x, y, config, &color);

			const int step = 5;
			buffer.setColor(color);
			for(int i = 0; i < step; i++)
				for(int j = 0; j < step; j++)
					buffer.drawPixel(x * step + i, y * step + j);
		}
}
