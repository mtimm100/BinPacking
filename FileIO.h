/***************************************************************
  Student Name: Mikayla Timm
  File Name: FileIO.h
  Assignment number 4

 * This file outlines the file IO functions for reading from
 * bins.txt and binItems.txt
***************************************************************/
#ifndef FILEIO_H
#define	FILEIO_H
#include <stdio.h>
#include <stdlib.h>
#include "AdjacencyList.h"
typedef struct Files *FilesP;

struct Files{
    FILE *bins;
    FILE *binItems;
};
/*
 * Opens bins.txt and binItems.txt for reading. Stores in the struct
 */
FilesP openFiles();
/*
 * Gets the next integer from the file binItems.txt.
 */
int getNextIntBinItems(FilesP files);
/*
 * Reads in specified number of integers in a file, returns the array of those ints
 */
int *getItemValues(FilesP files, int numItems);
/*
 * Reads in all of the bin sizes. puts them in an array.
 * Closes the bins stream when finished.
 */
int *getBinSizes(FilesP files);
#endif	/* FILEIO_H */

