#include "../common.h"

extern Arr* cfg;
extern Arr* img;
extern Arr* cell;

int cellInit(Arr* ar, Arr* _, ArrAc* ac) {
    char *val = arrGet(img, ac);
    Env *env = cfg->data;
    for (char i = 0; i < cfg->size[0]; i++)
        /* it looks highly platform-dependent */
        if (!memcmp(val, &env[i].color, (size_t) ar->eSize)) {
            ac->data = &i;
            arrSet(ar, ac);
        }
    return 0;
}

int cellMap(Arr* ar, Arr* ar2, ArrAc* ac) {
    Cell c = ARR_GET(Cell, ar, ac) ^ 1;
    ac->data = &c;
    arrSet(ar2, ac);
    return 0;
}
