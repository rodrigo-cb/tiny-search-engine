# Makefile for CS50 Indexer and Indextest
#
# CS50

MAKE = make

PROG1 = indexer
OBJS1 = indexer.o ../common/pagedir.o ../common/index.o ../common/word.o# indextest.o

PROG2 = indextest
OBJS2 = indextest.o ../common/index.o

LIBS = ../libcs50/libcs50.a

CFLAGS = -Wall -pedantic -std=c11 -ggdb -I../common -I../libcs50
CC = gcc
MAKE = make

.PHONY: all test clean

all: $(PROG1) $(PROG2)

$(PROG1): $(OBJS1)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

$(PROG2): $(OBJS2)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@


test: $(PROG) datafile
	./$(PROG) < datafile

clean:
	rm -f *~ *.o *.dSYM
	rm -f $(PROG1)
	rm -f $(PROG2)
	rm -f stocks
