#pragma once

#include <cstdlib>
#include "../config.h"
#include "../../common.h"
#include <dlfcn.h>
#include <QtCore/QString>

class DLLConfig : public Config
{
    Q_OBJECT

    DLLConfig(const DLLConfig& );
    DLLConfig& operator=(const DLLConfig& );

    /*
     *  DLL data
     */
    void *lib_handle;
    void (*lib_calc)();
    void* (*lib_data)();
    QString dll_path; // TODO: save DLL on serializtion
    /*
     *  Model data
     */
    void *data;
    int size_x, size_y;

    /*
     *  Generic constructor
     */
    void loadMeFromLibrary();

public:
    Q_INVOKABLE DLLConfig();
    Q_INVOKABLE DLLConfig(const QString& path);
    virtual ~DLLConfig();

    virtual int setIteration(int iteration) override;
    virtual int getIterationsCount() override { return current_iteration_id; }

    virtual void* getData(void* = NULL) override { return data; }
    virtual int getDimSize(int dim) const override;
    virtual int getDimSizeX() const override { return size_x; }
    virtual int getDimSizeY() const override { return size_y; }
    virtual int getDimSizeZ() const override { return 1; }

    virtual void serialize  (QDataStream& stream) override;
    virtual void deserialize(QDataStream& stream) override;
};
