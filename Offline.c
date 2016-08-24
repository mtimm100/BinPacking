/***************************************************************
  Student Name: Mikayla Timm
  File Name: Offline.c
  Assignment number 4

 *Implements the offline algorithm functions.
***************************************************************/
#include "Offline.h"
#include <stdlib.h>
#include <stdio.h>

/*
 * Creates an offline struct.
 * Runs all the offline algorithms.
 */
OfflineP runOffline(int numItems, int *binValues, int *itemValues){
    OfflineP offline = newOffline(numItems, binValues);
    //sort the items first
    qsort(itemValues, numItems, sizeof(int), cmpfunc);
    fprintf(stderr, "\nRunning offline first fit.\n");
    offline = offlineFirstFit(offline, itemValues, binValues);
    fprintf(stderr, "\nRunning offline best fit.\n");
    offline = offlineBestFit(offline, itemValues, binValues);
    return offline;
}

/*
 * Creates a new "offline" struct that holds all of the lists
 */
OfflineP newOffline(int numItems, int *binValues){
    OfflineP offline = (OfflineP)malloc(sizeof(struct Offline));
    offline->numItems = numItems;
    offline->firstList = newAdjList(binValues[0]);
    offline->bestList = newAdjList(binValues[0]);
    return offline;
}
/*
 * Frees the space taken by the offline struct
 */
OfflineP freeOffline(OfflineP offline){
    freeAdjList(offline->bestList);
    freeAdjList(offline->firstList);
    free(offline);
    return NULL;
}
/*
 * Offline First fit. Looks starting from first bin for a bin that will
 * fit the item. If one not found, makes a new bin.
 */
OfflineP offlineFirstFit(OfflineP offline, int *itemValues, int *binValues){
    BinP currentBin; 
    int binValueCounter = 1, i;
    for(i=0; i < offline->numItems; i++){
        currentBin = offline->firstList->firstBin;
        //find first bin that it will fit in.
        while(currentBin->nextBin != NULL && currentBin->remainingSpace < itemValues[i]){
            currentBin = currentBin->nextBin;
        }
        //terminated at last bin AND it is not big enough. make a new bin and try to add.
        if(currentBin->nextBin == NULL && currentBin->remainingSpace < itemValues[i]){
            addItemToNewBin(currentBin->nextBin, offline->firstList, binValues[binValueCounter++], itemValues[i]);
        }
        //terminated at a bin somewhere in the list and item will fit.
        else{
            addItem(currentBin, itemValues[i]);
        }
    }
    return offline;
}
/*
 * Offline Best Fit. Looks through all of the bins to find the one that will fill up the most
 * space (bin with least remaining space if item were added). 
 * Adds it to that bin after checking all of the bins.
 * If it doesn't fit in any, makes a new bin.
 */
OfflineP offlineBestFit(OfflineP offline, int *itemValues, int *binValues){
    BinP bestBin;
    int foundAFit;
    int binValueCounter = 1, i;
    for(i=0; i < offline->numItems; i++){
        foundAFit = 0;
         //find bin in which the item will fill the most space
        bestBin = findBestBin(offline->bestList->firstBin, itemValues[i], &foundAFit);
        if(foundAFit == 0){
            //didn't fit in any bins. try adding to a new one.
            BinP newBin = addBin(offline->bestList, binValues[binValueCounter++]);
            addItem(newBin, itemValues[i]);
        }
        //found a bin somewhere in the list and item will fit the best there.
        else{
            addItem(bestBin, itemValues[i]);
        }
    }
    return offline;
}
/*
 * Compare function used in the qsort for sorting the numbers in descending order.
 */
int cmpfunc(const void *a, const void *b){
    if(*(int*)a < *(int*)b)
        return 1;
    else if(*(int*)a > *(int*)b)
        return -1;
    else
        return 0;
}
