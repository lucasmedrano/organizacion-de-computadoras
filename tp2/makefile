CC = gcc
CFLAGS = -Wall
TARGET = cache

all:  cache.o set.o bloque.o
	$(CC) $(CFLAGS) -o $(TARGET) cache.o set.o bloque.o

cache.o:    cache.c
	$(CC) $(CFLAGS) -c cache.c cache.h

set.o:  set.c
	$(CC) $(CFLAGS) -c set.c set.h

bloque.o:   bloque.c
	$(CC) $(CFLAGS) -c bloque.c bloque.h
