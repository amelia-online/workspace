CC=gcc
CFLAGS=-std=gnu17 -I./include -Wall -Wpedantic -Wextra
SRC=src/main.c src/impl.c
INCLUDE=include/ws/impl.h
OBJS=impl.o

.PHONY: install clean
ws: src/main.c $(OBJS)
	$(CC) $(CFLAGS) src/main.c $(OBJS) -o ws
	
impl.o: src/impl.c include/ws/impl.h
	$(CC) $(CFLAGS) -c src/impl.c

install:
	rm ~/bin/ws
	cp ws ~/bin/

clean:
	rm ./*.o ./ws