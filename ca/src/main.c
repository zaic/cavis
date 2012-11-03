#include "common.h"

int main(int argc, char** argv) {
    if (argc < 3) {
        puts("usage:\tca <config dir> <iteration count>");
        return 0;
    }
    if (hppInit(argv[1])) {
        ELOG("initialization error");
        return -1;
    }
    for (int i = 0; i < atoi(argv[2]); i++) {
        if(hppMkStep()) {
            ELOG("can't perform next step");
            return -1;
        }
        void* data = hppGet();
    }
    hppDeinit();
    return 0;
}
