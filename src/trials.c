#include "../inc/trials.h"

int testRankNecklacePCR3(int *alpha, int n){
    if (!isNecklacePCR3(alpha,n)) return -1;
    sumArrBy1(alpha,n);
    return PCR3CountN(alpha,n);
}
int* testGetClosestNeckInDBSeqPCR3(int rank, int n){
    int* closestNeck = malloc(sizeof(int)*n);
    getClosestNeckInDBSeq(rank,n,closestNeck);
    return closestNeck;
}
int testRankLyndonWordPCR3(int *alpha, int n){
    if (!isNecklacePCR3(alpha,n)) return -1;
    sumArrBy1(alpha,n);
    return PCR3CountL(alpha,n);
}

int testRankDBseqPCR3(int *alpha, int n){
    return getRank(alpha,n);
}
int* testUnrankDBseqPCR3(int rank, int n){
    int* string = malloc(sizeof(int)*n);
    unrank(rank,n,string);
    return string;
}
