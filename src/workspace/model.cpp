#include "model.h"

Model::Model()
{

}

Model::~Model()
{

}

void Model::draw()
{
    buffer->create(renderer->getBufferFormat());
    renderer->setConfig(config);
    renderer->setBuffer(buffer);
    renderer->draw();
    buffer->complete();
}

void Model::save(QDataStream &stream)
{
    config->serialize(stream);
}

void Model::load(QDataStream &stream)
{
    config = new DLLConfig;
    config->deserialize(stream);
}
