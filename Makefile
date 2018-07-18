# Makefile for CS50 Tiny Search Engine
#
# David Kotz - April 2016, 2017
# updated by Xia Zhou, July 2018

MAKE = make
.PHONY: all valgrind clean

############## default: make all libs and programs ##########
all: 
	$(MAKE) -C libcs50
	$(MAKE) -C common
	$(MAKE) -C crawler

############## valgrind all programs ##########
valgrind: all
	$(MAKE) -C crawler valgrind

############## clean  ##########
clean:
	rm -f *~
	$(MAKE) -C libcs50 clean
	$(MAKE) -C common clean
	$(MAKE) -C crawler clean
