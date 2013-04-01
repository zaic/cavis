#pragma once

#include <cstddef>
#include <QtCore>

class Config : public QObject
{
    Q_OBJECT

    Config(const Config& );
    Config& operator=(const Config& );

protected:
    int current_iteration_id;

    Config();

    void preSerialize  (QDataStream& stream);
    void preDeserialize(QDataStream& stream);

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

    virtual void serialize  (QDataStream& ) { /* not implemented */ }
    virtual void deserialize(QDataStream& ) { /* not implemented */ }
};
