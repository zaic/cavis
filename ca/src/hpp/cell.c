#include "../common.h"

extern Arr* cfg;
extern Arr* img;
extern Arr* cell;

int cellInit(Arr* ar, Arr* _, ArrAc* ac) {
    char* val = (char*) arrGet(img, ac);
    Env* env = cfg->data;
    for (int i = 0; i < cfg->size[0]; i++)
        /* it looks highly platform-dependent */
        if (!memcmp(val, &env[i].color, (size_t) ar->eSize)) {
            char c = (char) i;
            ac->data = &c;
            if (arrSet(ar, ac)) {
                ELOG("can't set value");
                return -1;
            }
        }
    return 0;
}

int cellMap(Arr* ar, Arr* ar2, ArrAc* ac) {
    Cell* cp = (Cell*) arrGet(ar, ac);
    if (!cp) {
        ELOG("can't get value");
        return -1;
    }
    Cell c = *cp ^ 1;
    ac->data = &c;
    if(arrSet(ar2, ac)) {
        ELOG("can't set value");
        return -1;
    }
    return 0;
}
