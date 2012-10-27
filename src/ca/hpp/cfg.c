#include "../common.h"

int envCount;
int mvCount;

Arr* cfgRead(const char* path) {
    RAII_VAR(FILE*, fD, fopen(path, "r"), fclose);
    Arr* ar = cfgFRead(fD);
    if (!ar)
        ELOG("error while reading %s\n", path);
    return ar;
}

static void fReadDoubles(double *data, int size, FILE* fD) {
    for (int i = 0; i < size; i++)
        fscanf(fD, "%lf", &data[i]);
}

Arr* cfgFRead(FILE* fD) {
    if (!fD) {
        ELOG("null file descriptor");
        return NULL;
    }
    fscanf(fD, "%d%d", &envCount, &mvCount);
    Arr* cfg = arrAlloc(sizeof(Env), 1, envCount);
    Env* env = cfg->data;
    for (int i = 0; i < envCount; i++) {
        fscanf(fD, "%x", &env->color);
        fReadDoubles(env->mv, mvCount, fD);
        env += sizeof(Env);
    }
    return cfg;
}
