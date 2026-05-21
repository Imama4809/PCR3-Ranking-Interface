// #include "common.c"
#include <stdlib.h>

int sumWeightFirstJ(int alpha[], int j);

int checkPreSuf(int alpha[],int pre1,int pre2,int suf1);

int findLargestS(int alpha[], int j, int t, int n);

int S(int n, int w, int **tableS);

int sumWeightFirstJ(int alpha[], int j);

int findLargestS(int alpha[], int j, int t, int n);

int isNecklacePCR1(int *arr, int n);

int compareRotation(const int *arr, int n, int r);

void rotateLeft(const int *src, int *dest, int n, int shift);

int S(int n, int w, int **tableS);

void initializeTables(
    int n,
    int ****tableB,
    int ****tableP,
    int ***tableS
);

void freeTables(
    int n,
    int ***tableB,
    int ***tableP,
    int **tableS
);

int isGreater(int *arr, int *alpha, int n);

int GreatestNecklaceSmallerThan(int *alpha, int n);

int gcd(int a, int b);

int phi(int n);

int mu(int n);

int minPeriod(const int *arr, int n);

int xS(int n, int w, int j, int **tableS);

int B(int t, int j, int w, int alpha[], int ***tableB);

int P(int t, int j, int w, int alpha[], int ***tableP);

int A(
    int n,
    int t,
    int j,
    int w,
    int alpha[],
    int ***tableB,
    int ***tableP,
    int **tableS
);

int T(int n, int w, int alpha[]);

int N(int n, int w, int alpha[]);

int L(int n, int w, int alpha1[]);
