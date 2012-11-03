#include "../common.h"

Arr* arrAlloc(int eSize, int dim, ...) {
    Arr* ar = malloc(sizeof(Arr));
    if (!ar) {
        ELOG("can't allocate memory");
        return NULL;
    }
    ar->eSize = eSize;
    ar->dim = dim;
    va_list args;
    va_start(args, dim);
    for (int k = 0; k < dim; k++)
        ar->size[k] = va_arg(args, int);
    va_end(args);
    if (arrInit(ar))
        ELOG("array wasn't initialized");
    return ar;
}

void arrFree(Arr* ar) {
    arrDeinit(ar);
    free(ar);
}

int arrInit(Arr* ar) {
    if (!ar) {
        ELOG("null pointer");
        return -1;
    }
    int dataSize = ar->eSize;
    for (int k = 0; k < ar->dim; k++)
        dataSize *= ar->size[k];
    if (!(ar->data = malloc(dataSize))) {
        ELOG("can't allocate memory");
        return -1;
    }
    return 0;
}

void arrDeinit(Arr* ar) {
    free(ar->data);
    ar->data = NULL;
}

void* arrGet(Arr* ar, ArrAc* ac) {
#define NORMALIZE(k) {\
    ac->ix[k] %= ar->size[k];\
    if (ac->ix[k] < 0)\
        ac->ix[k] += ar->size[k];\
}
    if (!ar) {
        ELOG("null pointer")
        return NULL;
    }
    if (!ac) {
        ELOG("null pointer")
        return NULL;
    }
    int offset = 0;
    for (int k = 0; k < ar->dim - 1; k++) {
#ifdef ARR_TORUS
        NORMALIZE(k);
#endif
#ifdef ARR_BOUND_CHECK
        if (ac->ix[k] < 0 || ac->ix[k] >= ar->size[k]) {
            ELOG("accessor index out of bounds");
            return NULL;
        }
#endif
        offset = (offset + ac->ix[k]) * ar->size[k + 1];
    }
#ifdef ARR_TORUS
    NORMALIZE(ar->dim - 1);
#endif
    offset += ac->ix[ar->dim - 1];
    return ar->data + offset * ar->eSize;
#undef NORMALIZE
}

int arrSet(Arr* ar, ArrAc* ac) {
    void* p = arrGet(ar, ac);
    if (!p) {
        ELOG("can't set null pointer");
        return -1;
    }
    memcpy(p, ac->data, ar->eSize);
    return 0;
}

int arrMap(Arr* ar, Arr* ar2, int (*fn)(Arr*, Arr*, ArrAc*)) {
    /* we don't check the second argument since this function can be used for 
     * in-place update
     */
    if (!ar) {
        ELOG("null pointer");
        return -1;
    }
    if (!fn) {
        ELOG("null pointer");
        return -1;
    }
    ArrAc ac = { ar->dim, {}, NULL };
    int k = ar->dim - 1;
    while (1) {
        if (fn(ar, ar2, &ac)) {
            ELOG("function app failed");
            return -1;
        }
        while (k >= 0 && ++ac.ix[k] == ar->size[k])
            ac.ix[k--] = 0;
        if (k >= 0)
            k = ar->dim - 1;
        else
            break;
    }
    return 0;
}
