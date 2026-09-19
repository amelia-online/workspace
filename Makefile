CC=gcc
CFLAGS=-std=c17
SRC=src/main.c

ws: src/main.c
	$(CC) $(CFLAGS) src/main.c -o ws
	