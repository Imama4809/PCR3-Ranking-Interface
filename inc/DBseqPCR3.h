#include "helper.h"

void moveFrontUntilEndOfMax0ToBack(int *arr, int n, int place);

int maxZeroBetweenFrontAndBackNextNecklace(int *arr, int n);

int checkIfNextBest0DigitsAreAllZero(
    int arr[],
    int startIndex,
    int max0,
    int n
);

int confirmIfValid(
    int arr[],
    int beforeNecklace[],
    int seperation,
    int n
);

int getCount(
    int givenString[],
    int startIndex,
    int maxLen,
    int isMax0InWrapAround,
    int n
);

int getRank(int arr[], int n);

void switchIndex(int *arr, int i, int j);

int getClosestNeckInDBSeq(int rank, int n, int *closestNeck);

void greatestPCR3Below(int *alpha, int n);

void unrank(int rank, int n, int *string);

int DB(int *alpha, int n, int **stringSize);

int cutDownDB(int *alpha, int sizeCutDown, int n, int** stringSize);

int rankCutDownDB(int *neck, int *alpha, int sizeCutDown, int n);

// int* createDBseq(int startingStr, int n);
