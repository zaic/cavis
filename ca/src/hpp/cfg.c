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

static int fReadDoubles(double* data, int size, FILE* fp) {
    for (int i = 0; i < size; i++)
        if (1 != fscanf(fp, "%lf", &data[i]))
            return -1;
    return 0;
}

Arr* cfgFRead(FILE* fp) {
    if (!fp) {
        ELOG("null file descriptor");
        return NULL;
    }
    if (2 != fscanf(fp, "%d%d", &envCount, &mvCount)) {
        ELOG("can't read file");
        return NULL;
    }
    Arr* cfg = arrAlloc(sizeof(Env), 1, envCount);
    Env* env = cfg->data;
    for (int i = 0; i < envCount; i++) {
        if (1 != fscanf(fp, "%x", &env[i].color)) {
            ELOG("can't read file");
            return NULL;
        }
        if (fReadDoubles(env[i].mv, MIN(mvCount, HPP_MAX_NEIGHBOURS_COUNT), fp)) {
            ELOG("can't read file");
            return NULL;
        }
    }
    return cfg;
}
