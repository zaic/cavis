#include "dlltest.h"

#define size_x 192
#define size_y 128
#define size ((size_x) * (size_y))

char *next_data;
char *prev_data;

static char simple_u_random(float prob) {
    int r = rand();
    float fr = (float)r / RAND_MAX;
    return (fr < prob);
}

static void simple_swap() {
    char *tmp = next_data;
    next_data = prev_data;
    prev_data = tmp;
}

void init()
{
    prev_data = (char*)malloc(size);
    next_data = (char*)malloc(size);
    for(int i = 0; i < size_x; i++) {
        float prob = (float)i / (size_x - 1);
        for(int j = 0; j < size_y; j++)
            for(int k = 0; k < 4; k++)
                if(simple_u_random(prob))
                    prev_data[j * size_x + i] |= (1 << k);
    }
}

void calc()
{
    static const int dir[][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };
    memset(next_data, 0, size);
    for(int j = 0; j < size_y; j++)
        for(int i = 0; i < size_x; i++) {
            int z = j * size_x + i;
            for(int k = 0; k < 4; k++) {
                int jj = j + dir[k][0];
                int ii = i + dir[k][1];
                if(jj < 0 || jj >= size_y || ii < 0 || ii >= size_x) continue;
                int zz = jj * size_x + ii;
                int id = (k + 2) % 4;
                if(prev_data[zz] & (1 << id))
                    next_data[z] |= (1 << id);
            }
        }
    simple_swap();
}

void* data()
{
    return prev_data;
}

void quit()
{
    free(prev_data);
    free(next_data);
}
