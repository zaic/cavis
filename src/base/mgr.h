#pragma once

typedef struct {
    Type type;
    void* data;
} Obj;

void* (* get)(Obj*, Obj*);

void (* set)(Obj*, Obj*);
