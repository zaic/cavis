#pragma once

#include <QtWidgets>
#include "model.h"

class Project
{
    Project(const Project& );
    Project& operator=(const Project& );

    QMap<QMdiSubWindow*, Model*> models;

public:
    Project();
    ~Project();

    void addModel(QMdiSubWindow *model_win, Model *model_obj) { models[model_win] = model_obj; }
    Model* getModel(QMdiSubWindow *model_win) { return models[model_win]; }
};
