#pragma once

#include <cstddef>

// TODO: add some factory for creating needed ConfigClass for opened model?

class Config
{
    Config(const Config& );
    Config& operator=(const Config& );

protected:
    int current_iteration_id;

    Config();

public:
    virtual ~Config();

    static const int FORCED_UPDATE = -1807;

    virtual int prevIteration() { return setIteration(current_iteration_id - 1); }
    virtual int nextIteration() { return setIteration(current_iteration_id + 1); }
    virtual int setIteration(int) = 0;
    virtual int getIterationsCount() { return 0; }

    virtual void* getData(void* data_type = NULL) = 0;
    virtual int getDimSize(int dim) const = 0;
    virtual int getDimSizeX() const { return getDimSize(0); }
    virtual int getDimSizeY() const { return getDimSize(1); }
    virtual int getDimSizeZ() const { return getDimSize(2); }
};
