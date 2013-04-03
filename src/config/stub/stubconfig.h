#pragma once

#include "../config.h"
#include <cstring>
#include <QDebug>

class StubConfig : public Config
{
    Q_OBJECT

    int real_x, real_y;
    char *real_data;

public:
    StubConfig(int x = 30, int y = 20);
    virtual ~StubConfig();

    virtual int setIteration(int iteration);
    virtual int getIterationsCount() { return real_y - 2; }

    virtual void* getData(void* = NULL) { return real_data; }
    virtual int getDimSize(int dim) const;
    virtual int getDimSizeX() const { return real_x; }
    virtual int getDimSizeY() const { return real_y; }
    virtual int getDimSizeZ() const { return 1; }

    virtual void serialize  (QDataStream& stream);
    virtual void deserialize(QDataStream& stream);
};
