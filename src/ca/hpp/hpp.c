#include <stdlib.h>
#include <stdio.h>

#include "hpp.h"
#include "../core/arr.h"
#include "../core/log.h"
#include "../core/util.h"

typedef uchar Cell;

static int printIx(Arr* ar, Arr* _, ArrAc* ac) {
    char c = 3;
    ac->data = &c;
    if(arrSet(ar, ac)) {
        ELOG("can't set value\n");
        return -1;
    }
    return 0;
}

int hppRun() {
    RAII_VAR(Arr*, ar, arrAlloc(1, 3, 4, 4, 4), arrFree);
    arrMap(NULL, NULL, NULL);
    return 0;
}
