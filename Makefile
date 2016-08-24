CFLAGS = -g -Wall
CC = gcc

objects = AdjacencyList.o FileIO.o Online.o Offline.o BinPackingTest.o 

test : $(objects)
	  $(CC) -o test $(objects) 

AdjacencyList.o : AdjacencyList.c AdjacencyList.h
	  gcc -c -Wall AdjacencyList.c
FileIO.o : FileIO.c FileIO.h AdjacencyList.h
	  gcc -c -Wall FileIO.c
Online.o : Online.c Online.h AdjacencyList.h FileIO.h
	  gcc -c -Wall Online.c
Offline.o : Offline.c Offline.h Online.h
	  gcc -c -Wall Offline.c
BinPackingTest.o : BinPackingTest.c AdjacencyList.h FileIO.h Online.h Offline.h
	  gcc -c -Wall BinPackingTest.c

.PHONY : clean
clean : 
	  rm test $(objects)
