#include "../common.h"

static int printIx(Arr* ar, Arr* _, ArrAc* ac) {
    char c = 3;
    ac->data = &c;
    if(arrSet(ar, ac)) {
        ELOG("can't set value\n");
        return -1;
    }
    return 0;
}

void hppInit(const char* dir) {
}

void hppNext() {
}

void hppDeinit() {
}

void* hppGet() {
}

int hppRun() {
    RAII_VAR(Arr*, ar, arrAlloc(1, 3, 4, 4, 4), arrFree);
    arrMap(NULL, NULL, NULL);
    return 0;
}
