#include "visualizzzator.h"

Visualizzzator::Visualizzzator(Config *_config, Renderer *_renderer) :
	config(_config),
	renderer(_renderer)
{

}

Visualizzzator::~Visualizzzator() {

}

void Visualizzzator::draw() {
	buffer->create();
	renderer->setConfig(config);
	renderer->setBuffer(buffer);
	renderer->draw();
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
