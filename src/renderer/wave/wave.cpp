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

    const float max_value = 4.0 * 7.0;
    const int r = 5;
    float *gl_values = buffer->getGLData();
    uchar* data = reinterpret_cast<uchar*>(config->getData());
    for(int i = 0; i < config->getDimSizeY(); i++)
        for(int j = 0; j < config->getDimSizeX(); j++) {
            int id = i * config->getDimSizeX() + j;
            double res = 0.0;
            int rescnt = 0;
#if 1
            for(int ri = 0; ri <= 2*r; ri++)
                for(int rj = 0; rj <= 2*r; rj++) {
                    int ii = i + ri - r;
                    int jj = j + rj - r;
                    if(0 <= ii && ii < config->getDimSizeY() && 0 <= jj && jj < config->getDimSizeX()) {
                        res += __builtin_popcount(data[ii * config->getDimSizeX() + jj]) / max_value;
                        rescnt++;
                    }
                }
#else
            res = float(data[id]) / 255;
            rescnt = 1;
#endif
            gl_values[id] = static_cast<float>(res / rescnt);
        }
}
