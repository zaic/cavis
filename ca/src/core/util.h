#pragma once

#define RAII_VAR(type, name, val, dtor)\
    void name ## dtor (type* v) { dtor(*v); }\
    type name __attribute__((cleanup(name ## dtor))) = (val)
