# Makefile for CS50 Crawler
#
# CS50

MAKE = make

PROG = crawler
OBJS = crawler.o ../common/pagedir.o
LIBS = ../libcs50/libcs50.a

CFLAGS = -Wall -pedantic -std=c11 -ggdb -I../common -I../libcs50
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
