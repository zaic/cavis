#include "stubconfig.h"

StubConfig::StubConfig(int x, int y) : real_x(x), real_y(y)
{
    real_data = new char[x * y];
}

StubConfig::~StubConfig()
{
    delete[] real_data;
}

int StubConfig::getDimSize(int dim) const
{
    switch(dim) {
    case 0: return real_x;
    case 1: return real_y;
    default: return 1;
    }
    return 100500;
}

int StubConfig::setIteration(int iteration)
{
    if(iteration < 0) return current_iteration_id;
    if(iteration > getIterationsCount()) return current_iteration_id;
    qDebug() << "[config/stub] set iteration to " << iteration;
    current_iteration_id = iteration;
    memset(real_data, 0, real_x * real_y);
    switch(iteration) {
    case 0:
        real_data[real_x + 5] = 6;
        break;
    default:
        real_data[real_x + 5 + iteration] = 2;
        real_data[real_x * (iteration + 1) + 5] = 4;
        break;
    }
    return iteration;
}
