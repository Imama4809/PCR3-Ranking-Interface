#include "../inc/DBseqPCR3.h"
#include "../inc/PCR3NeckAndLyndon.h"

void moveFrontUntilEndOfMax0ToBack(int *arr,int n,int place){
    if (!arr || n <= 0) return;
    if (place < 0 || place >= n) return;       // nothing to do or invalid
    int m = place;                          // count to rotate (inclusive)
    if (m == n) return;                         // whole array would be moved -> no change

    int dum_count = m;
    int dum[dum_count];

    for (int i = 0; i < dum_count; i++) {dum[i] = arr[i];}
    for (int i = 0; i < n - m; i++) {arr[i] = arr[i + m];}
    for (int i = 0; i < dum_count; i++) {arr[n - m + i] = dum[i];}

}

int maxZeroBetweenFrontAndBackNextNecklace(int *arr,int n){
    int count = 0; // count how many leading zeros
    while (count < n && arr[count] == 0) {count++;}
    for (int i = 0; i < n - count; i++) {arr[i] = arr[i + count];}
    for (int i = n - count; i < n; i++) {arr[i] = 1;}
    // printf(" ");
    smallestPCR3StrictlyAbove(arr,n);
    return count;
}

int checkIfNextBest0DigitsAreAllZero(int arr[], int startIndex, int max0, int n){
    for (int i=0;i<max0;i++){
        if (arr[(startIndex+i)%n] != 0){
            return 0;
        }
    }
    return 1;
}


int confirmIfValid(int arr[], int beforeNecklace[], int seperation, int n){
    int afterNecklace[n];
    if (!isNecklacePCR3(beforeNecklace,n)) {return 0;}
    int integerRepresentation = binToNum(beforeNecklace,n);
    integerRepresentation--;
    numToBin(integerRepresentation,n,afterNecklace);
    greatestPCR3Below(afterNecklace,n);
    for (int i = seperation;i<n;i++){
        if (afterNecklace[i-seperation] != arr[i]){
            return 0;
        }
    }
    return 1;

}


int getCount(int givenString[],int startIndex, int maxLen, int isMax0InWrapAround, int n){
    int arr[n];
    for (int i=0;i<n;i++){arr[i] = givenString[i];}
    // int areAllIndiciesAfterMax0EqualTo1;
    if (startIndex == 0 || isMax0InWrapAround) { // get rid of isMax0InWrapAround and see if it still works
        int val = maxZeroBetweenFrontAndBackNextNecklace(arr,n);
        if (!confirmIfValid(givenString,arr,val,n)){return -1;}
        sumArrBy1(arr,n);
        return PCR3Count(arr,n) -primLength(arr,n)  + val;
    } else {
        moveFrontUntilEndOfMax0ToBack(arr,n,startIndex+maxLen);
        if (!confirmIfValid(givenString,arr,startIndex+maxLen,n)){return -1;}
        sumArrBy1(arr,n);
        return PCR3Count(arr,n)-primLength(arr,n) +startIndex+maxLen;
    }
}

int getRank(int arr[],int n) {
    int dum[n];
    for (int i=0;i<n;i++){
        dum[i] = arr[i];
        // PCR3ToPCR1(dum,n);
    }
    int numZeros;
    if (is_zeros_then_ones(arr,n,&numZeros)) return numZeros; 
    if (isNecklacePCR3(dum,n)){
        // printf("    ");
        // for (int m=0;m<n;m++){printf("%d",arr[m]);}
        // printf("   ");
        sumArrBy1(arr,n);
        return PCR3Count(arr,n);
    }

    int maxLen = 0;
    int startIndex = -1;
    
    int prefixLen = 0;
    int suffixLen = 0;


    // int areAllIndiciesAfterMax0EqualTo1 =1;
    int isMax0InWrapAround = 0;

    // Linear scan for the usual max run
    int bestLen = 0, bestStart = -1;
    int curLen = 0, curStart = -1;

    for (int i = 0; i < n; i++) {
        if (arr[i] == 0) {
            if (curLen == 0) curStart = i;
            curLen++;
            if (curLen > bestLen) {
                bestLen = curLen;
                bestStart = curStart;
            }
        } else {
            curLen = 0;
        }
    }

    // Consider wrap-around only if first and last elements are zero
    if (arr[0] == 0 && arr[n - 1] == 0) {
        // Count zeros at start
        while (prefixLen < n && arr[prefixLen] == 0) prefixLen++;

        // Count zeros at end
        int j = n - 1;
        while (j >= 0 && arr[j] == 0) { suffixLen++; j--; }

        int wrapLen = prefixLen + suffixLen;

        // If the entire array is zeros, max is n starting at 0
        if (wrapLen >= n) {
            bestLen = n;
            bestStart = 0;
        } else if (wrapLen > bestLen) {
            isMax0InWrapAround = 1;
            bestLen = wrapLen;
            // Start where the suffix run begins
            bestStart = j + 1;  // j stopped on the first non-zero before the suffix
        }
    }

    maxLen = bestLen;

    int arrayOfMax0[n];
    int indexOfArrayOfMax0 = 0;

    //for loop gets all of the places in the array where the max0 is present
    for (int i=0;i<n;i++){
        if (checkIfNextBest0DigitsAreAllZero(arr,i,maxLen,n)){ 
            arrayOfMax0[indexOfArrayOfMax0] = i;
            i = i+maxLen;
            indexOfArrayOfMax0++;
        }
    }

    //following for loop will check all the differences between these values and take the smallest one

    startIndex = (bestLen >= 0) ? bestStart : 0;
    // printf("SI: %d, ML: %d ",startIndex,maxLen);
    if (indexOfArrayOfMax0 == 1){
        return getCount(arr,startIndex,maxLen,isMax0InWrapAround,n);
    } else {
        for (int j=0;j<indexOfArrayOfMax0;j++){
            if (arrayOfMax0[j]+maxLen > n){isMax0InWrapAround = 1;}
            else {isMax0InWrapAround = 0;}
            if (getCount(arr,arrayOfMax0[j],maxLen,isMax0InWrapAround,n) != -1){
                return getCount(arr,arrayOfMax0[j],maxLen,isMax0InWrapAround,n);
            }  
        }
    }
    return -1;
}
//, int **closestNecklace, int* closestNecklacePosition

void switchIndex(int *arr, int i, int j){
    int val = arr[i];
    arr[i] = arr[j];
    arr[j] = val;
}


int getClosestNeckInDBSeq(int rank, int n, int* closestNeck){
    for (int i = 0;i < n;i++) closestNeck[i] = 0;
    int temp;
    for (int i=0;i<n;i++){
        closestNeck[i] = 1;
        temp = getRank(closestNeck,n);
        for (int j = 0;j < n;j++) --closestNeck[j];
        // for (int j = 0;j < n;j++) printf("%d",closestNeck[j]);
        // printf(" %d ",temp);
        // printf("\n");
        if (temp < rank){
            closestNeck[i] = 1;
            continue;
        }
        else if (temp < rank + n){
            return temp;
        } else {
            closestNeck[i] = 0;
        }
    }
    return -1;
}

void unrank(int rank, int n, int *string){
    if (rank < n){
        for (int i =0;i<rank;i++) string[i] = 0;
        for (int i =0;i<n-rank;i++) string[rank+i] = 1;
        return;
    }

    // int *neck = malloc(sizeof(int)*n);
    int *beta1 = malloc(sizeof(int)*n);
    int *beta2 = malloc(sizeof(int)*n);
    int neckPos = getClosestNeckInDBSeq(rank,n,beta1); // O(n)
    for (int i=0;i<n;i++) beta2[i] = beta1[i];
    // beta2[n-1] = 1;
    greatestPCR3Below(beta2,n); // O(n)
    int shift =  neckPos - rank;
    if (shift == 0){
        for (int i=0;i<n;i++)string[i] = beta1[i];
        return;
    }
    int b1p = shortest_repeating_length(beta1,n); // O(n)
    // int b2p = shortest_repeating_length(beta2,n); // O(n)
    // printf(" shift : %d ", shift);
    // printf(" beta1 :");
    // for (int i = 0;i<b1p;i++) printf("%d",beta1[i]);
    // printf(" beta2 :");
    // for (int i = 0;i<b2p;i++) printf("%d",beta2[i]);
    if (b1p == n){
        for (int i = 0;i<n-shift;i++){
            string[i] = beta1[i+shift];
        }
        for (int i =0;i<shift;i++){
            string[n-shift + i] = beta2[i];
        }
    } else {
        for (int i = 0;i<b1p-shift;i++){
            string[i] = beta1[i+shift];
        }
        for (int i =0;i<n-b1p+shift;i++){
            string[b1p-shift + i] = beta2[i];
        }
    }
    // printf(" string :");
    // for (int i = 0;i<n;i++) printf("%d",string[i]);
    // printf(" \n");
    free(beta1);
    free(beta2);
    return;
}


void DB(int *alpha, int n) {
    while (!smallestPCR3Neck(alpha,n)) {
        for (int i =0;i<primLength(alpha,n);i++){
            printf("%d",alpha[i]);
            if (primLength(alpha,n) == 1) return;
        }
        greatestPCR3Below(alpha,n);
        // printf("\n");
    }
    // return;
}


// alpha gaurunteed to be an Alt necklace
void cutDownDB(int *alpha, int* cutdown,int cutdownArrLen, int n){
    int primLen;
    //need to find the strings that have substrings that are going to be cutout

    int currentCutLen;
    int (*cutLocations)[n] = calloc(cutdownArrLen, sizeof(*cutLocations));
    int *cutdownNecklacesRank = malloc(sizeof(int)*cutdownArrLen);
    for (int i =0;i<cutdownArrLen;i++){
        printf("%d\n",cutdown[i]);
        currentCutLen = cutdown[i];
        if (currentCutLen == 1){
            cutdownNecklacesRank[i] = n;
            // for (int j=0;j<n;j++){
            //     printf("%d ",cutLocations[i][j]);
            // }
            // printf("\n");
            continue;
        }
        for (int j=0;j<=n-currentCutLen;j++){
            if (j%currentCutLen == 0){
                cutLocations[i][j] = 1;
            }
        }

        
        // for (int j=0;j<n;j++){
        //     printf("%d ",cutLocations[i][j]);
        // }
        cutdownNecklacesRank[i] = getRank(cutLocations[i],n);
        // printf("\n");
    }


    int curCutOut= 0;
    int isCut = 0;
    while (!smallestPCR3Neck(alpha,n)) {
        primLen = primLength(alpha,n);
        if (getRank(alpha,n) == cutdownNecklacesRank[curCutOut]){
            isCut = 1;
            curCutOut++;
        }
        delArrBy1(alpha,n);
        for (int i =0;i<primLen;i++){
            if (isCut){
                i = i + cutdown[curCutOut-1]+1;
                isCut=0; 
                if (i >= primLen){
                    if (primLen == 1) return;
                    break;
                }
            }
            
            if (primLen == 1) {
                if (i < primLen) printf("%d",alpha[i]+1);
                return;
            }
            printf("%d",alpha[i]);
        }
        greatestPCR3Below(alpha,n);
    }
    printf("\n");
}