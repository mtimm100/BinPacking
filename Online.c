/***************************************************************
  Student Name: Mikayla Timm
  File Name: Online.c
  Assignment number 4

 * Online.c implements all of the online algorithms for bin packing.
***************************************************************/
#include "Online.h"
#include "AdjacencyList.h"
/*
 * Creates an online struct.
 * Runs all the online algorithms.
 */
OnlineP runOnline(int numItems, int *binValues, int *itemValues){
    OnlineP online = newOnline(numItems, binValues);
    fprintf(stderr, "\nRunning online first fit.\n");
    online = onlineFirstFit(online, itemValues, binValues);
    fprintf(stderr, "\nRunning online best fit.\n");
    online = onlineBestFit(online, itemValues, binValues);
    fprintf(stderr, "\nRunning online next fit.\n");
    online = onlineNextFit(online, itemValues, binValues);
    return online;
}
/*
 * Creates a new "online" struct that holds all of the lists
 */
OnlineP newOnline(int numItems, int *binValues){
    OnlineP online = (OnlineP)malloc(sizeof(struct Online));
    online->numItems = numItems;
    online->firstList = newAdjList(binValues[0]);
    online->nextList = newAdjList(binValues[0]);
    online->bestList = newAdjList(binValues[0]);
    return online;
}

/*
 * Frees the space taken by the online struct
 */
OnlineP freeOnline(OnlineP online){
    freeAdjList(online->bestList);
    freeAdjList(online->nextList);
    freeAdjList(online->firstList);
    free(online);
    return NULL;
}
/*
 * Online First fit. Looks starting from first bin for a bin that will
 * fit the item. If one not found, makes a new bin.
 */
OnlineP onlineFirstFit(OnlineP online, int *itemValues, int *binValues){
    BinP currentBin; 
    int binValueCounter = 1, i;
    for(i=0; i < online->numItems; i++){
        currentBin = online->firstList->firstBin;
        //find first bin that it will fit in.
        while(currentBin->nextBin != NULL && currentBin->remainingSpace < itemValues[i]){
            currentBin = currentBin->nextBin;
        }
        //terminated at last bin AND it is not big enough. make a new bin and try to add.
        if(currentBin->nextBin == NULL && currentBin->remainingSpace < itemValues[i]){
            
            addItemToNewBin(currentBin->nextBin, online->firstList, binValues[binValueCounter++], itemValues[i]);
        }
        //terminated at a bin somewhere in the list and item will fit.
        else{
            addItem(currentBin, itemValues[i]);
        }
    }
    return online;
}
/*
 * Online Best Fit. Looks through all of the bins to find the one that will fill up the most
 * space (bin with least remaining space if item were added). 
 * Adds it to that bin after checking all of the bins.
 * If it doesn't fit in any, makes a new bin.
 */
OnlineP onlineBestFit(OnlineP online, int *itemValues, int *binValues){
    BinP bestBin;
    int foundAFit;
    int binValueCounter = 1, i;
    for(i=0; i < online->numItems; i++){
        foundAFit = 0;
         //find bin in which the item will fill the most space
        bestBin = findBestBin(online->bestList->firstBin, itemValues[i], &foundAFit);
        if(foundAFit == 0){
            //didn't fit in any bins. try adding to a new one.
            BinP newBin = addBin(online->bestList, binValues[binValueCounter++]);
            addItem(newBin, itemValues[i]);
        }
        //found a bin somewhere in the list and item will fit the best there.
        else{
            addItem(bestBin, itemValues[i]);
        }
    }
    return online;
}
/*
 * Online Next Fit. if it fits in the current bin, places it there. 
 * Else tries to put it in a new bin.
 */
OnlineP onlineNextFit(OnlineP online, int *itemValues, int *binValues){
    BinP currentBin = online->nextList->firstBin;
    int binValueCounter = 1, i;
    for(i=0; i < online->numItems; i++){
        if(currentBin->remainingSpace >= itemValues[i]){
            //fits in current bin. add it
            addItem(currentBin, itemValues[i]);
        }
        else{
            //try adding to a new bin.
            addItemToNewBin(currentBin->nextBin, online->nextList, binValues[binValueCounter++], itemValues[i]);
            currentBin = currentBin->nextBin;
        }
    }
    return online;
}

/*
 * Adds the item to a new bin if it didn't fit in any others.
 * If it doesn't fit in the new bin, prints a message and tosses the item out
 */
void addItemToNewBin(BinP newBin, AdjacencyListP list, int binValue, int itemValue){
    newBin = addBin(list, binValue);
    if(itemValue > newBin->maxSize){
        //if it's too big for the new bin, just forget about the item and move on
        fprintf(stderr, "%d too large for current bin of size %d.\n", itemValue, newBin->maxSize);
    }
    else{
        addItem(newBin, itemValue);
    }
}
/*
 * Finds the bin in which the value fills the most of. returns the bin.
 * Returns NULL if value doesn't fit in any bins
 */
BinP findBestBin(BinP currentBin, int value, int *foundAFit){
    BinP bestBin = NULL;
    int bestRemSpace = 100;
    while(currentBin != NULL){
        if(currentBin->remainingSpace >= value 
                && (currentBin->remainingSpace - value) < bestRemSpace){
            *foundAFit = 1;
            bestBin = currentBin;
            bestRemSpace = bestBin->remainingSpace - value;
            
        }
        currentBin = currentBin->nextBin;
    }
    return bestBin;
}
