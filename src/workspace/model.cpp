#include "model.h"

Model::Model()
{

}

Model::~Model()
{

}

void Model::draw()
{
    buffer->create();
    renderer->setConfig(config);
    renderer->setBuffer(buffer);
    renderer->draw();
    buffer->complete();
}
