/***************************************************************
  Student Name: Mikayla Timm
  File Name: BinPackingTest.c
  Assignment number 4

 * This file calls all of the functions implemented in the other files in 
 * order to run the bin packing algorithms and compare the results.
 * Output all to the console. Reads in from bins.txt and binItems.txt
 * to perform offline and online binpacking algorithms.
***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "AdjacencyList.h"
#include "FileIO.h"
#include "Online.h"
#include "Offline.h"
/*
 * Prints all of the results of the bin packing algorithms
 */
void printResults(OnlineP online, OfflineP offline);
/*
 * Print how the items are packed in each bin in the list
 */
void printPackings(AdjacencyListP list);

int main() {
    FilesP files = openFiles();
    int numRuns = getNextIntBinItems(files);
    int *binValues = getBinSizes(files), *itemValues;
    int i, j, numItems;

    for(i=0; i < numRuns; i++){
        numItems = getNextIntBinItems(files);
        itemValues = (int *)malloc(sizeof(int) * numItems);
        for(j=0; j < numItems; j++){
            itemValues[j] = getNextIntBinItems(files);
        }   
        OnlineP online = runOnline(numItems, binValues, itemValues);
        OfflineP offline = runOffline(numItems, binValues, itemValues);
        printResults(online, offline);
        free(itemValues);
    }
    free(binValues);
    
    return 0;
}

/*
 * Prints all of the results of the bin packing algorithms
 */
void printResults(OnlineP online, OfflineP offline){
    
    printf("\n\nPolicy             Total Bins Used\n");
    printf("Online Algorithm\n");
    printf("  First Fit        %15d\n", online->firstList->numBins);
    printf("  Next Fit         %15d\n", online->nextList->numBins);
    printf("  Best Fit         %15d\n", online->bestList->numBins);
    printf("Offline Algorithm\n");
    printf("  First Fit        %15d\n", offline->firstList->numBins);
    printf("  Best Fit         %15d\n", offline->bestList->numBins);
    printf("\n\nOnline First Packings: \n");
    printPackings(online->firstList);
    printf("\n\nOnline Next Packings: \n");
    printPackings(online->nextList);
    printf("\n\nOnline Best Packings: \n");
    printPackings(online->bestList);
    printf("\n\nOffline First Packings: \n");
    printPackings(offline->firstList);
    printf("\n\nOffline Best Packings: \n");
    printPackings(offline->bestList);
    printf("\n\n-------------------------------------\n");
    
}
/*
 * Print how the items are packed in each bin in the list
 */
void printPackings(AdjacencyListP list){
    int i, j;
    ItemP currentItem;
    BinP currentBin = list->firstBin;
    fprintf(stderr, "numBins: %d\n", list->numBins);
    for(i=0; i < list->numBins; i++){
        fprintf(stderr, "\nBin %d: ", i+1);
        currentItem = currentBin->firstItem;
        fprintf(stderr, "\nBin size: %d\n", currentBin->maxSize);
        for(j=0; j < currentBin->numItems; j++){
            fprintf(stderr, "%d ", currentItem->value);
            currentItem = currentItem->nextItem;
        }
        currentBin = currentBin->nextBin;
    }
}
