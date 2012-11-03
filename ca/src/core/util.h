#pragma once

/* use it only when destructor function returns void */
#define RAII_VAR(type, name, val, dtor)\
    void name ## dtor (type* v) { dtor(*v); }\
    type name __attribute__((cleanup(name ## dtor))) = (val)

#define SWAP(x, y) {\
    unsigned char x ## y [sizeof(x) == sizeof(y) ? (signed) sizeof(x) : -1];\
    memcpy(x ## y,     &y, sizeof(x));\
    memcpy(    &y,     &x, sizeof(x));\
    memcpy(    &x, x ## y, sizeof(x));\
}
