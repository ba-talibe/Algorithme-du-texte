#
# This is an example Makefile for a countwords program.  This
# program uses both the scanner module and a counter module.
# Typing 'make' or 'make count' will create the executable file.
#

# define some Makefile variables for the compiler and compiler flags
# to use Makefile variables later in the Makefile: $()
#
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#
# for C++ define  CC = g++
CC = gcc
CFLAGS  = -g -Wall

# typing 'make' will invoke the first target entry in the file 
# (in this case the default target entry)
# you can name this target entry anything, but "default" or "all"
# are the most commonly used names by convention
#
default: main


main:  main.o algo_naif.o algo_rapide.o 
	$(CC) $(CFLAGS) -o main main.o algo_naif.o algo_rapide.o


main.o:  main.c algo_naif.h algo_rapide.h
	$(CC) $(CFLAGS) -c main.c


algo_naif.o:  algo_naif.c algo_naif.h 
	$(CC) $(CFLAGS) -c algo_naif.c

algo_rapide.o:  algo_rapide.c algo_rapide.h 
	$(CC) $(CFLAGS) -c algo_rapide.c



clean: 
	$(RM) count *.o *~