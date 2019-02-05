# Makefile for 'common' module

# PROG =
OBJS = pagedir.o
LIBS =

CFLAGS = -Wall -pedantic -std=c11 -ggdb -I../libcs50
MAKE = make
CC = gcc

default: $(OBJS)

pagedir.o: pagedir.h

.PHONY: clean

clean:
	rm -f *~ *.o *.dSYM