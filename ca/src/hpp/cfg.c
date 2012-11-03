#include "../common.h"

int envCount;
int mvCount;

Arr* cfgRead(const char* path) {
    RAII_VAR(FILE*, fd, fopen(path, "r"), fclose);
    Arr* ar = cfgFRead(fd);
    if (!ar)
        ELOG("error while reading %s", path);
    return ar;
}

static void fReadDoubles(double *data, int size, FILE* fd) {
    for (int i = 0; i < size; i++)
        fscanf(fd, "%lf", &data[i]);
}

Arr* cfgFRead(FILE* fd) {
    if (!fd) {
        ELOG("null file descriptor");
        return NULL;
    }
    fscanf(fd, "%d%d", &envCount, &mvCount);
    Arr* cfg = arrAlloc(sizeof(Env), 1, envCount);
    Env* env = cfg->data;
    for (int i = 0; i < envCount; i++) {
        fscanf(fd, "%x", &env->color);
        fReadDoubles(env->mv, mvCount, fd);
        env += sizeof(Env);
    }
    return cfg;
}
