#include "wave.h"

WaveRenderer::WaveRenderer() : parameters(NULL)
{

}

WaveRenderer::~WaveRenderer()
{

}

void WaveRenderer::draw()
{
    qDebug() << "[render/wave] start drawing, x =" << config->getDimSizeX() << "and y =" << config->getDimSizeY();
    buffer->setGLSize(config->getDimSizeX(), config->getDimSizeY());
    buffer->prepare();

    const float max_value = 4.0;
    float *gl_values = buffer->getGLData();
    uchar* data = reinterpret_cast<uchar*>(config->getData());
    for(int i = 0; i < config->getDimSizeY(); i++)
        for(int j = 0; j < config->getDimSizeX(); j++) {
            int id = i * config->getDimSizeX() + j;
            gl_values[id] = __builtin_popcount(data[id]) / max_value;
        }
}
