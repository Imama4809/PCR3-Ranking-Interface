#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define k 2

int *compute_lps(const int arr[], int n);

int shortest_repeating_length(const int arr[], int n);

int isArrayBigger(int *arr1, int *arr2, int n);

int binToNum(int *ptr, int n);

void numToBin(int num, int len, int *ptr);

void PCR1ToPCR3(int alpha[], int n);

void PCR3ToPCR1(int alpha[], int n);

int sumWeight(int alpha[], int len);

int isNecklacePCR1(int *arr, int n);

int isNecklacePCR3(int *arr, int n);

bool is_zeros_then_ones(const int arr[], int n, int *numZeros);

int primLength(const int *a, int n);

void sumArrBy1(int *arr,int n);

void findNextGreatestNecklace(int string[], int n);

int smallestPCR3StrictlyAbove(int *alpha, int n);

int countUniqueRotationsPCR3(int *arr, int n);

void greatestPCR3Below(int *alpha, int n);