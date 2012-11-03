#include "common.h"

int main(int argc, char** argv) {
    if (argc < 3) {
        puts("usage:\tca <config dir> <iteration count>");
        return 0;
    }
    hppInit(argv[1]);
    for (int i = 0; i < atoi(argv[2]); i++) {
        hppMkStep();
        void* data = hppGet();
    }
    hppDeinit();
    return 0;
}
