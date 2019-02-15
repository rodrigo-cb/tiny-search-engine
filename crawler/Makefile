# Makefile for CS50 Crawler
#
# CS50

MAKE = make

PROG = crawler
OBJS = crawler.o
LIBS = ../common/common.a ../libcs50/libcs50.a 

CFLAGS = -Wall -pedantic -std=c11 -ggdb -I../common -I../libcs50
CC = gcc
MAKE = make

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

.PHONY: clean

clean:
	rm -f *~ *.o *.dSYM
	rm -f $(PROG)
	rm -f stocks
