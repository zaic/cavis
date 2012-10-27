#pragma once

#include <stdio.h>

#include "arr.h"

Arr* pngRead(const char*);

Arr* pngFRead(FILE*);

int pngWrite(Arr*, const char*);

int pngFWrite(Arr*, FILE*);
