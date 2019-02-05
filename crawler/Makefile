# Makefile for CS50 Crawler
#
# CS50

MAKE = make
.PHONY: all valgrind clean

PROG = crawler
OBJS = crawler.o
LIBS =

# uncomment the following to turn on verbose memory logging
# TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING)#-I../common
CC = gcc
MAKE = make

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

#crawler.o: crawler.h
.PHONY: test clean

test: $(PROG) datafile
	./$(PROG) < datafile

clean:
	rm -f *~ *.o *.dSYM
	rm -f $(PROG)
	rm -f stocks
