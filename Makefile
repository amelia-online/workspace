CC=gcc
CFLAGS=-std=c17 -I./include -g -fsanitize=address
SRC=src/main.c src/impl.c
INCLUDE=include/ws/impl.h
OBJS=impl.o

ws: src/main.c $(OBJS)
	$(CC) $(CFLAGS) src/main.c $(OBJS) -o ws
	
impl.o: src/impl.c include/ws/impl.h
	$(CC) $(CFLAGS) -c src/impl.c