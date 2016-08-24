/***************************************************************
  Student Name: Mikayla Timm
  File Name: Online.h
  Assignment number 4

 * Online.h outlines all of the functions for bin packing.
 * Stores all the fit info in a struct for printing at the end of each run.
***************************************************************/
#ifndef ONLINE_H
#define	ONLINE_H


#include "AdjacencyList.h"
#include "FileIO.h"
#include <stdlib.h>

typedef struct Online *OnlineP;

struct Online{
    int numItems;
    AdjacencyListP nextList;
    AdjacencyListP firstList;
    AdjacencyListP bestList;
};

/*
 * Creates an online struct.
 * Runs all the online algorithms.
 */
OnlineP runOnline(int numItems, int *binValues, int *itemValues);
/*
 * Creates a new "online" struct that holds all of the lists
 */
OnlineP newOnline(int numItems, int *binValues);
/*
 * Frees the space taken by the online struct
 */
OnlineP freeOnline(OnlineP online);
/*
 * Online First fit. Looks starting from first bin for a bin that will
 * fit the item. If one not found, makes a new bin.
 */
OnlineP onlineFirstFit(OnlineP online, int *itemValues, int *binValues);
/*
 * Online Best Fit. Looks through all of the bins to find the one that will fill up the most
 * space (bin with least remaining space if item were added). 
 * Adds it to that bin after checking all of the bins.
 * If it doesn't fit in any, makes a new bin.
 */
OnlineP onlineBestFit(OnlineP online, int *itemValues, int *binValues);
/*
 * Online Next Fit. if it fits in the current bin, places it there. 
 * Else tries to put it in a new binz
 */
OnlineP onlineNextFit(OnlineP online, int *itemValues, int *binValues);
/*
 * Adds the item to a new bin if it didn't fit in any others.
 */
void addItemToNewBin(BinP currentBin, AdjacencyListP list, int binValue, int itemValue);
/*
 * Finds the bin in which the value fills the most of. returns the bin.
 * Returns NULL if value doesn't fit in any bins
 */
BinP findBestBin(BinP firstBin, int value, int *foundAFit);

#endif	/* ONLINE_H */