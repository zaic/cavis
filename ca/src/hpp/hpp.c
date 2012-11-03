#include "../common.h"

Arr* cfg;
Arr* img;
Arr* lat;
Arr* latBuf;

int hppInit(const char* dir) {
    chdir(dir);
    cfg = cfgRead("env");
    if (!cfg) {
        ELOG("can't open env file");
        return -1;
    }
    img = pngRead("img");
    if (!img) {
        ELOG("con't open img file");
        return -1;
    }
    lat = arrAlloc(1, 2, img->size[0], img->size[1]);
    latBuf = arrAlloc(1, 2, img->size[0], img->size[1]);
    arrMap(lat, NULL, cellInit);
    return 0;
}

int hppMkStep() {
    arrMap(lat, latBuf, cellMap);
    SWAP(lat, latBuf);
    return 0;
}

void hppDeinit() {
    arrFree(cfg);
    arrFree(img);
    arrFree(lat);
    arrFree(latBuf);
}

void* hppGet() {
    return NULL;
}
