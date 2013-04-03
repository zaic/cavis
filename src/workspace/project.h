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
    QMap<Model*, QSet<QMdiSubWindow*>> windows;

public:
    Project();
    ~Project();

    /*
     *  Model functions
     */
    Model* addModel(const QStringList& renderers, Config *config);
    Model* getModel(QMdiSubWindow *win);
    void removeModel(QMdiSubWindow *win);
    void removeModel(Model *model_obj);

    /*
     *  Object functions
     */
    QMdiSubWindow* addWindowToModel(Model *model_obj, QtSimpleBuffer *buf);
    void removeWindowFromModel(QMdiSubWindow *win);

#if 0
    void addModel(QMdiSubWindow *model_win, Model *model_obj) { models[model_win] = model_obj; }
    Model* getModel(QMdiSubWindow *model_win) { return models[model_win]; }
    void remModel(QMdiSubWindow *model_win);
#endif

    QString getFilename() const { return proj_filename; }
    void save(const QString& filename);
    void load(const QString& filename, QMdiArea *mdi_area);
};
