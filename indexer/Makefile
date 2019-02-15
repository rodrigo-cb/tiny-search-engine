# Makefile for CS50 indexer
#
# CS50

MAKE = make

PROG1 = indexer
OBJS1 = indexer.o

PROG2 = indextest
OBJS2 = indextest.o 

LIBS = ../common/common.a ../libcs50/libcs50.a

CFLAGS = -Wall -pedantic -std=c11 -ggdb -I../common -I../libcs50
CC = gcc
MAKE = make

.PHONY: all clean

all: $(PROG1) $(PROG2)

$(PROG1): $(OBJS1)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@


$(PROG2): $(OBJS2)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@
	
clean:
	rm -f *~ *.o *.dSYM
	rm -f $(PROG1)
	rm -f $(PROG2)
	rm -f stocks