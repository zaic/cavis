#pragma once

#include <stdio.h>

#include "../core/arr.h"

typedef struct {
    int color;
    double mv[HPP_MAX_NEIGHBOURS_COUNT];
} Env;

Arr* cfgRead(const char*);

Arr* cfgFRead(FILE*);