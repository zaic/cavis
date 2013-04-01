#pragma once

#include <QtWidgets>
#include <cassert>
#include "model.h"

#include "config/dll/dllconfig.h"
#include "buffer/qt_buffer/qtsimplebuffer.h"

class Project
{
    Project(const Project& );
    Project& operator=(const Project& );

    QString proj_filename;

    QMap<QMdiSubWindow*, Model*> models;

public:
    Project();
    ~Project();

    void addModel(QMdiSubWindow *model_win, Model *model_obj) { models[model_win] = model_obj; }
    Model* getModel(QMdiSubWindow *model_win) { return models[model_win]; }
    void remModel(QMdiSubWindow *model_win);

    QString getFilename() const { return proj_filename; }
    void save(const QString& filename);
    void load(const QString& filename, QMdiArea *mdi_area);
};
