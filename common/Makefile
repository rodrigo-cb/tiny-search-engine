# Makefile for 'common' module

# PROG =
OBJS = pagedir.o index.o word.o
LIB = common.a
LIBS = ../libcs50/libcs50.a

CFLAGS = -Wall -pedantic -std=c11 -ggdb -I../libcs50
MAKE = make
CC = gcc

# default: $(OBJS)
# pagedir.o: pagedir.h

# Build the library by archiving object files
$(LIB): $(OBJS)
	ar cr $(LIB) $(OBJS) $(LIBS)

# Dependencies: object files depend on header files
pagedir.o: pagedir.h
index.o: index.h
word.o: word.h

.PHONY: clean

# clean:
# 	rm -f *~ *.o *.dSYM
# clean up after our compilation
clean:
	rm -f $(LIB) *~ *.o