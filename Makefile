############################################################
#	Project: Polynomial library
#	File: Makefile
#	Version: 1.0
#	Date: December 22, 2017
#
#		(C) Alejandro Santorum Varela
#			 alejandro.santorum@gmail.com
#			 alejandro.santorum@estudiante.uam.es
#
############################################################
CC = gcc -ansi -pedantic
CFLAGS = -Wall
EXE = pol_test

all : $(EXE)

.PHONY : clean
clean :
	rm -f *.o core $(EXE)

$(EXE) : % : %.o polynomial.o
	$(CC) $(CFLAGS) -o $@ $@.o polynomial.o -lm

polynomial.o : polynomial.c polynomial.h
	$(CC) $(CFLAGS) -c $<
