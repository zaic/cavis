# vim: set noet:

CC = gcc
CFLAGS = -w -std=c11

CORE = arr.o png.o
HPP = hpp.o
OUT = hpp
LIBS = -lpng

.PHONY: all debug release clean

all: debug
debug: CFLAGS += -g
release: CFLAGS += -O3 -Wall -Wextra -Wunused -Wshadow -Wunsafe-loop-optimizations

debug release: $(OUT)

hpp: $(CORE) $(HPP)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

$(CORE): cfg.h log.h

clean:
	rm -f *.o $(OUT)
