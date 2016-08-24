/***************************************************************
  Student Name: Mikayla Timm
  File Name: AdjacencyList.h
  Assignment number 4

 * This file outlines all of the functions as well as data structures
 * for an adjacency list-type structure that holds bins and items.
***************************************************************/

#ifndef ADJACENCYLIST_H
#define	ADJACENCYLIST_H


#include <stdlib.h>

typedef struct Item *ItemP;
typedef struct Bin *BinP;
typedef struct AdjacencyList *AdjacencyListP;

struct Item{
    int value;
    ItemP nextItem;
};

struct Bin{
    int numItems;
    int maxSize;
    int remainingSpace;
    ItemP firstItem;//head ptr
    BinP nextBin;
};

struct AdjacencyList{
    int numBins;
    BinP firstBin; //head ptr
};

/*
 * Creates a new adjacency list 
 */
AdjacencyListP newAdjList(int firstBinValue);
/*
 * Frees the space taken by the adjacency list
 */
AdjacencyListP freeAdjList(AdjacencyListP adjList);
/*
 * Adds a new bin to the list
 */
BinP addBin(AdjacencyListP adjList, int maxBinSize);
/*
 * Creates a new bin
 */
BinP newBin(int maxSize);
/*
 * frees the space taken by a bin
 */
BinP freeBin(BinP bin);
/*
 * Adds an item to a bin
 */
void addItem(BinP bin, int value);
/*
 * Creates a new item containing the value passed in
 */
ItemP newItem(int value);
/*
 * Frees the space taken by the item
 */
ItemP freeItem(ItemP item);

        
#endif	/* ADJACENCYLIST_H */

