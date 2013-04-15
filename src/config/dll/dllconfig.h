#pragma once

#include <cstdlib>
#include <cassert>
#include "../config.h"
#include "../../common.h"
#include "ca/model.h"
#include <dlfcn.h>
#include <QtCore/QString>
#include <QtWidgets>

class DLLConfig : public Config
{
    Q_OBJECT

    DLLConfig(const DLLConfig& );
    DLLConfig& operator=(const DLLConfig& );

    /*
     *  DLL data
     */
    model_t *obj_model;
    void *lib_handle;
    void (*lib_makestep)(model_t*);
    arr2_u8_t* (*lib_get_lattice)(model_t*);
    QString dll_path; // TODO: save DLL on serializtion
    QString cfg_path; // TODO: the same

    /*
     *  Model data
     */
    arr2_u8_t *obj_data;
    int size_x, size_y;

    /*
     *  Generic constructor
     */
    bool loadMeFromLibrary();

public:
    Q_INVOKABLE DLLConfig();
    Q_INVOKABLE DLLConfig(const QString& path);
    virtual ~DLLConfig();

    virtual int setIteration(int iteration) override;
    virtual int getIterationsCount() override { return current_iteration_id; }

    virtual void* getData(void* = NULL) override { return obj_data->_; }
    virtual int getDimSize(int dim) const override;
    virtual int getDimSizeX() const override { return size_x; }
    virtual int getDimSizeY() const override { return size_y; }
    virtual int getDimSizeZ() const override { return 1; }

    virtual void serialize  (QDataStream& stream) override;
    virtual void deserialize(QDataStream& stream) override;
};
