#include "dlltest.h"

#define size_x 256
#define size_y 192
#define size ((size_x) * (size_y))

char *next_data;
char *prev_data;

static char simple_u_random(float prob)
{
    int r = rand();
    float fr = (float)r / RAND_MAX;
    return (fr < prob ? 1 : 0);
}

static void simple_swap()
{
    char *tmp = next_data;
    next_data = prev_data;
    prev_data = tmp;
}

void init()
{
    srand(0);
    prev_data = (char*)malloc(size);
    memset(prev_data, 0, size);
    next_data = (char*)malloc(size);
    for(int i = 0; i < size_x; i++) {
        for(int j = 0; j < size_y; j++) {
            int di = abs(i - size_x / 2);
            int dj = abs(j - size_y / 2);
            float prob = (di * di + dj * dj <= 256 ? .9 : .1);
            for(int k = 0; k < 4; k++)
                if(simple_u_random(prob))
                    prev_data[j * size_x + i] |= (1 << k);
        }
    }
}

void calc()
{
    static const int dir[][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };
    memset(next_data, 0, size);
    for(int j = 0; j < size_y; j++) {
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

            if(i == 0 && (prev_data[z] & 0x8)) next_data[z] |= 0x2;
            if(i == size_x - 1 && (prev_data[z] & 0x2)) next_data[z] |= 0x8;
            if(j == 0 && (prev_data[z] & 0x1)) next_data[z] |= 0x4;
            if(j == size_y - 1 && (prev_data[z] & 0x4)) next_data[z] |= 0x1;

            if((next_data[z] == (0x1 | 0x4) || next_data[z] == (0x2 | 0x8)) && simple_u_random(.5))
                next_data[z] ^= 0xF;
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
