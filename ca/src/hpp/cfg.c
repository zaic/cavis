#include "../common.h"

int envCount;
int mvCount;

Arr* cfgRead(const char* path) {
    FILE* fp = fopen(path, "r");
    if (!fp) {
        ELOG("can't open file \"%s\" for reading", path);
        return NULL;
    }
    Arr* ar = cfgFRead(fp);
    if (!ar)
        ELOG("error while reading \"%s\"", path);
    if (fclose(fp))
        ELOG("can't close file \"%s\"", path);
    return ar;
}

static void fReadDoubles(double* data, int size, FILE* fp) {
    for (int i = 0; i < size; i++)
        fscanf(fp, "%lf", &data[i]);
}

Arr* cfgFRead(FILE* fp) {
    if (!fp) {
        ELOG("null file descriptor");
        return NULL;
    }
    fscanf(fp, "%d%d", &envCount, &mvCount);
    Arr* cfg = arrAlloc(sizeof(Env), 1, envCount);
    Env* env = cfg->data;
    for (int i = 0; i < envCount; i++) {
        fscanf(fp, "%x", &env->color);
        fReadDoubles(env->mv, mvCount, fp);
        env += sizeof(Env);
    }
    return cfg;
}
