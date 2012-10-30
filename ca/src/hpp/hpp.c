#include "../common.h"

void hppInit(const char* dir) {
}

void hppNext() {
}

void hppDeinit() {
}

void* hppGet() {
    return NULL;
}

int hppRun() {
    RAII_VAR(Arr*, ar, arrAlloc(1, 3, 4, 4, 4), arrFree);
    arrMap(NULL, NULL, NULL);
    return 0;
}
