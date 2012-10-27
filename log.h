#pragma once

#define ELOG(fmt, ...) fprintf(stderr, "%s: " fmt, __FUNCTION__, ##__VA_ARGS__);
