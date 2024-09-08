.PHONY: all clean

CC:=gcc
CFLAGS+=-O3 -g -Wall -Wextra -no-pie
LDFLAGS = -lm

all: main

main: main.c Heron.c  LUT_method.c taylor.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -rf main