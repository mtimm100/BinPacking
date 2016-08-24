/***************************************************************
  Student Name: Mikayla Timm
  File Name: Offline.h
  Assignment number 4

 *Outlines all of the functions needed for performing offline 
 * bin packing algorithms.
***************************************************************/

#ifndef OFFLINE_H
#define	OFFLINE_H

#include "Online.h" //for using the basic functions finding best bin etc
#include <stdlib.h>

typedef struct Offline *OfflineP;

struct Offline{
    int numItems;
    AdjacencyListP firstList;
    AdjacencyListP bestList;
};
/*
 * Creates an offline struct.
 * Runs all the offline algorithms.
 */
OfflineP runOffline(int numItems, int *binValues, int *itemValues);
/*
 * Creates a new "offline" struct that holds all of the lists
 */
OfflineP newOffline(int numItems, int *binValues);
/*
 * Frees the space taken by the offline struct
 */
OfflineP freeOffline(OfflineP offline);
/*
 * Offline First fit. Looks starting from first bin for a bin that will
 * fit the item. If one not found, makes a new bin.
 */
OfflineP offlineFirstFit(OfflineP offline, int *itemValues, int *binValues);
/*
 * Offline Best Fit. Looks through all of the bins to find the one that will fill up the most
 * space (bin with least remaining space if item were added). 
 * Adds it to that bin after checking all of the bins.
 * If it doesn't fit in any, makes a new bin.
 */
OfflineP offlineBestFit(OfflineP offline, int *itemValues, int *binValues);
/*
 * Compare function used in the qsort for sorting the numbers in descending order.
 */
int cmpfunc(const void *a, const void *b);

#endif	/* OFFLINE_H */

