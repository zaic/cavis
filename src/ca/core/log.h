#pragma once

#define ELOG(fmt, ...) fprintf(stderr, "%s:%d @%s: " fmt, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__);
