CC = gcc
CFLAGS = -Wall
TARGET = qsort

all:  qsort.o orgaqsortassembly.o
	$(CC) $(CFLAGS) -o $(TARGET) qsort.o orgaqsortassembly.o

qsort.o:  qsort.c
	$(CC) $(CFLAGS) -c qsort.c

orgaqsortassembly.o:  orgaqsortassembly.s
	$(CC) $(CFLAGS) -c orgaqsortassembly.s
