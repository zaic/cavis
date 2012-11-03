#pragma once

#define ELOG(fmt, ...) fprintf(stderr, "%s:%d @%s: " fmt "\n", __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__);

#define DLOG(fmt, ...) fprintf(stderr, "@%s: " fmt "\n", __FUNCTION__, ##__VA_ARGS__);
