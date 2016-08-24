/***************************************************************
  Student Name: Mikayla Timm
  File Name: FileIO.c
  Assignment number 4

 * This file implements all of the necessary file input, reading 
 * from bins.txt and binItems.txt.
***************************************************************/
#include "FileIO.h"
#define NUMBINS 1000


/*
 * Opens bins.txt and binItems.txt for reading. Stores in the struct
 */
FilesP openFiles(){
    FilesP files = (FilesP)malloc(sizeof(struct Files));
    files->binItems = fopen("binItems.txt", "r");
    files->bins = fopen("bins.txt", "r");
    return files;
}
/*
 * Gets the next integer from the file binItems.txt.
 */
int getNextIntBinItems(FilesP files){
    int num;
    fscanf(files->binItems, "%d", &num);
    return num;
}
/*
 * Reads in specified number of integers in a file, returns the array of those ints
 */
int *getItemValues(FilesP files, int numItems){
    int *values = (int *)malloc(sizeof(int) * numItems);
    int i;
    int currentNum;
    for(i=0; i < numItems; i++){
        fscanf(files->binItems, "%d", &currentNum);
        values[i] = currentNum;
    }
    return values;
}
/*
 * Reads in all of the bin sizes. puts them in an array.
 * Closes the bins file pointer when finished.
 */
int *getBinSizes(FilesP files){
    int i;
    int currentNum;
    int *binSizes = (int *)malloc(sizeof(int) * NUMBINS);
    for(i=0; i < NUMBINS; i++){
        fscanf(files->bins, "%d", &currentNum);
        binSizes[i] = currentNum;
    }
    fclose(files->bins);
    return binSizes;
}



