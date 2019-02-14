# Makefile for CS50 Tiny Search Engine
#
# CS50

MAKE = make
.PHONY: all valgrind clean

############## default: make all libs and programs ##########
all: 
	$(MAKE) -C libcs50
	$(MAKE) -C common
	$(MAKE) -C crawler
	$(MAKE) -C indexer

############## valgrind all programs ##########
valgrind: all
	$(MAKE) -C crawler valgrind
	$(MAKE) -C indexer valgrind

############## clean  ##########
clean:
	rm -f *~
	$(MAKE) -C libcs50 clean
	$(MAKE) -C common clean
	$(MAKE) -C crawler clean
	$(MAKE) -C indexer clean
