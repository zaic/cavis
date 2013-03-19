#pragma once

#include <set>
#include "model.h"

using std::set;

class Project
{
    Project(const Project& );
    Project& operator=(const Project& );

    set<Model*> models;

public:
    Project();
    ~Project();

    void addModel(Model *model) { models.insert(model); }
};
