#pragma once

/* PType = A | B ..
 * Type = PType PType | Ctype [Type]
 */

enum Mod { BUFFERED, DISTRIBUTED };

enum PType { BYTE };

typedef struct {
    Mod mod;
    union {
        PType pType;
        Type cType[TYPE_MAX_TYPE_PARAM_COUNT];
    } ctor;
} Type;
