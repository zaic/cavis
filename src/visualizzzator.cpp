#include "visualizzzator.h"

Visualizzzator::Visualizzzator(Config *_config, Renderer *_renderer) :
    config(_config),
    renderer(_renderer)
{

}

Visualizzzator::~Visualizzzator()
{

}

void Visualizzzator::draw()
{
    buffer->create();
    renderer->setConfig(config);
    renderer->setBuffer(buffer);
    renderer->draw();
    buffer->complete();
}
