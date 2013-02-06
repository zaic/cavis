#include "visualizzzator.h"

Visualizzzator::Visualizzzator(Config *_config, Cut *_cut) :
	config(_config),
	cut(_cut)
{

}

Visualizzzator::~Visualizzzator() {

}

void Visualizzzator::draw(GraphicBuffer* buffer) {
	// TODO бегать нужно по логическому дву(трёх-)мерному пространству же!
	//     а пока что работает в предположении прямого отображения

	// TODO выпилить init и finalize (тогда и предыдущая тудушка не нужна)

	if(!buffer->prepare()) return ;
	cut->init(config, buffer);
	for(int y = 0; y < config->getRealDimSizeY(); y++)
		for(int x = 0; x < config->getRealDimSizeX(); x++) {
			cut->draw(x, y);
		}
	cut->finalize();
	buffer->complete();
#if 0
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
#endif
}
