/***************************************************************
  Student Name: Mikayla Timm
  File Name: AdjacencyList.c
  Assignment number 4

 * This file implements all of the necessary functions for
 * creating and adding structures to the "adjacency list"
 * of bins and items.
***************************************************************/
#include "AdjacencyList.h"
#include <stdlib.h>
#include <stdio.h>

/*
 * Creates a new adjacency list
 */
AdjacencyListP newAdjList(int firstBinValue){
    AdjacencyListP aList = (AdjacencyListP)malloc(sizeof(struct AdjacencyList));
    aList->firstBin = newBin(firstBinValue);
    aList->numBins = 1;
    return aList;
}
/*
 * Frees the space taken by the adjacency list
 */
AdjacencyListP freeAdjList(AdjacencyListP adjList){
    BinP temp = adjList->firstBin;
    //BinP temp2 = adjList->firstBin;
    while(adjList->firstBin != NULL){
        temp = adjList->firstBin;
        adjList->firstBin = adjList->firstBin->nextBin;
        freeBin(temp);
    }
    free(adjList);
    return NULL;
}
/*
 * Adds a new bin to the list
 */
BinP addBin(AdjacencyListP adjList, int maxBinSize){
    BinP bin = newBin(maxBinSize);
    adjList->numBins++;
    if(adjList->firstBin == NULL){
        adjList->firstBin = bin;
    }
    else{
        BinP currentBin = adjList->firstBin;
        while(currentBin->nextBin != NULL){
            currentBin = currentBin->nextBin;
        }
        currentBin->nextBin = bin;
    }
    return bin;
}
/*
 * Creates a new bin
 */
BinP newBin(int maxBinSize){
    BinP bin = (BinP)malloc(sizeof(struct Bin));
    bin->numItems = 0;
    bin->maxSize = maxBinSize;
    bin->remainingSpace = maxBinSize;
    bin->firstItem = NULL;//head ptr
    bin->nextBin = NULL;
    return bin;
}
/*
 * frees the space taken by a bin
 */
BinP freeBin(BinP bin){
    ItemP temp;
    while(bin->firstItem != NULL){
        temp = bin->firstItem;
        bin->firstItem = bin->firstItem->nextItem;
        freeItem(temp);
    }
    free(bin);
    return NULL;
}
/*
 * Creates a new item containing the value passed in
 */
ItemP newItem(int value){
    ItemP item = (ItemP)malloc(sizeof(struct Item));
    item->value = value;
    item->nextItem = NULL;
    return item;
}
/*
 * Frees the space taken by the item
 */
ItemP freeItem(ItemP item){
    free(item);
    return NULL;
}
/*
 * Adds an item to a bin
 */
void addItem(BinP bin, int value){
    ItemP currentItem = bin->firstItem;
    if(bin->maxSize < value){
        //don't put it in. return.
        fprintf(stderr, "%d too large for current bin of size %d.\n", value, bin->maxSize);
        return;
    }
    if(currentItem == NULL){
        //if first item not initialized, set it
        bin->firstItem = newItem(value);
    }
    else{
        //get to the end of the linked list of items in the bin
        while(currentItem->nextItem != NULL){
            currentItem = currentItem->nextItem;
        }
        currentItem->nextItem = newItem(value);
    }
    bin->remainingSpace -= value;
    bin->numItems++;
}