#pragma once

#include "cfg.h"
#include "util.h"

typedef struct {
    int eSize;
    int dim;
    int size[ARR_MAX_DIM];
    void* data;
} Arr;

typedef struct {
    int dim;
    int ix[ARR_MAX_DIM];
    void* data;
} ArrAc;

Arr* arrAlloc(int, int, ...);

void arrFree(Arr*);

int arrInit(Arr*);

void arrDeinit(Arr*);

void* arrGet(Arr*, ArrAc*);

int arrSet(Arr*, ArrAc*);

int arrMap(Arr*, Arr*, int (*)(Arr*, Arr*, ArrAc*));
