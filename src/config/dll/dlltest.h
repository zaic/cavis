#pragma once

#include <stdlib.h>
#include <string.h>

typedef void model_t;
typedef unsigned char arr2_u8_t;

model_t *create(const char *);
void destroy(model_t *);
void make_step(model_t *);
void print_rules(model_t *);
arr2_u8_t *average(model_t *);
