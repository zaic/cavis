#include "common.h"

int char2rgb(Arr* ar, Arr* ar2, ArrAc* ac) {
    char* cp = (char*) arrGet(ar, ac);
    if (!cp) {
        ELOG("can't get value");
        return -1;
    }
    char c = !*cp ? 0 : 0xff;
    char cs[3] = {c, c, c};
    ac->data = cs;
    if (arrSet(ar2, ac)) {
        ELOG("can't set value");
        return -1;
    }
    return 0;
}

int main(int argc, char** argv) {
    if (argc < 3) {
        puts("usage:\tca <config dir> <iteration count>");
        return 0;
    }
    Arr* img;
    if (hppInit(argv[1])) {
        ELOG("initialization error");
        return -1;
    }
    for (int i = 0; i < atoi(argv[2]); i++) {
        if(hppMkStep()) {
            ELOG("can't perform next step");
            return -1;
        }
        Arr* lat = hppGet();
        if (!img && lat)
            img = arrAlloc(3, 2, lat->size[0], lat->size[1]);
        char path[PATH_MAX];
        sprintf(path, "%04d", i);
        arrMap(lat, img, char2rgb);
        pngWrite(img, path);
        // test
    }
    hppDeinit();
    return 0;
}
