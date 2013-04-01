#pragma once

#include "../config.h"
#include <QDebug>
#include <QVector>
#include <QDir>

class LocalFileConfig : public Config
{
    LocalFileConfig(const LocalFileConfig& );
    LocalFileConfig& operator=(const LocalFileConfig& );

    int dim_size[3];
    QVector<double> data;
    QStringList iterations_list;
    QDir working_dir;
    QString data_path;

public:
    LocalFileConfig(const char *init_path = NULL);
    virtual ~LocalFileConfig();

    bool resetDirectory(const char *path);

    virtual int setIteration(int iteration_id);
    virtual int getIterationsCount() { return iterations_list.size() - 1; }

    virtual void* getData(void* data_type = NULL);
    virtual int getDimSize(int dim) const;
    virtual int getDimSizeX() const { return dim_size[0]; }
    virtual int getDimSizeY() const { return dim_size[1]; }
    virtual int getDimSizeZ() const { return dim_size[2]; }

    virtual void serialize  (QDataStream& stream);
    virtual void deserialize(QDataStream& stream);
};
