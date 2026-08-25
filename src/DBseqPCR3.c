#include "../inc/DBseqPCR3.h"
#include "../inc/PCR3NeckAndLyndon.h"
#include "../inc/helper.h"
#include "../inc/trials.h"
#include <math.h>

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
    greatestPCR3BelowNSS(arr,n);
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

    for (int i =0;i<n;i++){
        afterNecklace[i] = beforeNecklace[i];
    }
    int i =n-1;
    while (afterNecklace[i] == 0){
        afterNecklace[i] = 1;
        i--;
    }
    afterNecklace[i] = 0;
    // int integerRepresentation = binToNum(beforeNecklace,n);
    // integerRepresentation--;
    // numToBin(integerRepresentation,n,afterNecklace);
    
    
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
    if (startIndex == 0 || isMax0InWrapAround) { 
        int val = maxZeroBetweenFrontAndBackNextNecklace(arr,n);
        // for (int i=0;i<n;i++)printf("%d",arr[i]);
        // printf(" ");
        sumArrBy1(arr,n);
        // printf("%d %d %d ", PCR3CountNew(arr,n), primLength(arr,n), val);
        return PCR3CountNew(arr,n) - val;
    } else {
        moveFrontUntilEndOfMax0ToBack(arr,n,startIndex+maxLen);
        sumArrBy1(arr,n);
        return PCR3CountNew(arr,n)+primLength(arr,n) -startIndex-maxLen;
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
        int retVal = PCR3CountNew(arr,n);
        delArrBy1(arr,n);
        return retVal;
    }
    int guessStartIndex; 
    int guessMaxLen;
    int guessIsMax0InWrapAround;

    guessStartIndex = pcr3_shift_position(arr,n,&guessMaxLen,&guessIsMax0InWrapAround);
    //following for loop will check all the differences between these values and take the smallest one
    return getCount(arr,guessStartIndex,guessMaxLen,guessIsMax0InWrapAround,n);
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
    // printf("hello");
    closestNeck[0] = 1;
    for (int i=1;i<n;i++){
        fflush(stdout);
        closestNeck[i] = 1;
        temp = getRank(closestNeck,n);
        if (temp > rank){
            continue;
        }
        else if (temp >= rank -n){
            return temp;
        } else {
            closestNeck[i] = 0;
        }
    }
    return -1;
}

void unrank(int rank, int n, int *string){
    if (rank >= (int)pow(2,n) - n){
        for (int i =0;i<(int)pow(2,n) - rank;i++) string[i] = 0;
        for (int i =(int)pow(2,n) - rank;i<n;i++) string[i] = 1;
        return;
    }

    // int *neck = malloc(sizeof(int)*n);
    int *beta1 = malloc(sizeof(int)*n*2);
    int neckPos = getClosestNeckInDBSeq(rank,n,beta1); // O(n)
    if (neckPos == rank){
        for (int i=0;i<n;i++){
            string[i] = beta1[i];
        }
        free(beta1);
        return;
    }
    for (int i=0;i<n;i++) beta1[i+n] = beta1[i];
    for (int i=n-1;;i--){
        if (beta1[i+n] == 1){
            beta1[i+n] = 0;
            break;
        }
        beta1[i+n] = 1;
    }
    greatestPCR3BelowNSS(beta1+n,n); // O(n)
    int shift =  rank - neckPos;
    if (shift == 0){
        for (int i=0;i<n;i++)string[i] = beta1[i];
        return;
    }
    int len = primLength(beta1,n);
    // printf("primlen: %d\n",len);
    if (primLength(beta1,n) != n){
        for (int i =0;i<n;i++){
            beta1[i+len] = beta1[i+n];
        }
    }
    // for (int i =0;i<n;i++) printf("%d",beta1[i]);
    // printf("\n");
    // for (int i =0;i<n;i++) printf("%d",beta1[i+n]);
    // printf("\n");
    for (int i=0;i<n;i++){
        string[i] = beta1[i+shift];
    }
    // printf(" string :");
    // for (int i = 0;i<n;i++) printf("%d",string[i]);
    // printf(" \n");
    free(beta1);
    return;
}


int DB(int *alpha, int n, int **stringPBR) {
    int *string = malloc(sizeof(int)*1);
    int stringLen = 0;
    // printf("Hello");
    while (1) {
        for (int i =0;i<primLength(alpha,n);i++){
            string[stringLen++] = alpha[i];
            if (primLength(alpha,n) == 1){
                // printString(string,stringLen); 
                *stringPBR = string;
                return stringLen; 
            }
            string = realloc(string,sizeof(int)*(stringLen+1));
            // printf("%d",string[stringLen-1]);
        }
        greatestPCR3Below(alpha,n);
        // printf("\n");
    }    
    
    // stringPBR = string;

    return -1;
}







//the following are the old cut down generation algorithms

int newCutDownDB(int sizeCutDown, int **stringPBR){
    int n = (sizeCutDown == 0) ? 1 : 32 - __builtin_clz(sizeCutDown);
    // printf("%d",n);
    int *closestNeck = malloc(sizeof(int)*n);
    sizeCutDown = pow(2,n)- sizeCutDown;
    int unCutDBSeq = getClosestNeckInDBSeq(sizeCutDown,n,closestNeck);
    // for (int i=0;i<n;i++) printf("%d",closestNeck[i]);
    // printf("\n");
    int *string = malloc(sizeof(int));
    int diff = sizeCutDown-unCutDBSeq;
    // printf("%d",diff);
    // printf("\n");
    fflush(stdout);
    int *cuts = malloc(sizeof(int));
    int stringLen = 0;

     if (diff == 0){
        stringLen = DB(closestNeck,n, &string);
        *stringPBR = string;
        return stringLen;
    }
    //the following code just gets all cuts and puts them in an array for easy access
    /***********************/
    int sizeCuts = 1;
    if (diff > (n+1)/2){
        cuts[sizeCuts-1] = (n+1)/2;
        cuts = realloc(cuts,++sizeCuts*sizeof(int));
        diff = diff-(n+1)/2;
        // if (diff > n/2 - 1){
        //     cuts[sizeCuts-1] = n/2-1;
        //     cuts = realloc(cuts,++sizeCuts*sizeof(int)); 
        //     diff = diff-(n/2-1);
        // }
    }
    cuts[sizeCuts-1] = diff;
    /***********************/
    qsort(cuts,sizeCuts,sizeof(int),cmp);


    //the following code will get all of the strings that will have values cut out of them
    /***********************/
    int currentCutLen;
    int (*cutLocations)[n] = calloc(sizeCuts, sizeof(*cutLocations));
    int *cutdownNecklacesRank = malloc(sizeof(int)*sizeCuts);
    for (int i =0;i<sizeCuts;i++){
        
        // printf("%d\n",string[i]);
        currentCutLen = cuts[i];
        if (currentCutLen == 1){
            cutdownNecklacesRank[i] = pow(2,n)-n;
            continue;
        }
        for (int j=0;j<=n-currentCutLen;j++){
            if (j%currentCutLen == 0){
                cutLocations[i][j] = 1;
            }
        }
        cutdownNecklacesRank[i] = getRank(cutLocations[i],n);
    }
    int curCutOut= 0;
    int isCut = 0;
    /***********************/
    int primLen;
    while (1) {
        primLen = primLength(closestNeck,n);
        if ((curCutOut < sizeCuts) && getRank(closestNeck,n) == cutdownNecklacesRank[curCutOut]){
            isCut = 1; 
            // printf("HERE");
        }
        // delArrBy1(closestNeck,n);
        for (int i =0;i<primLen;i++){
            if (isCut){
                i = i + cuts[curCutOut];
                isCut=0; 
                curCutOut++;
                if (primLen == 1) {
                    *stringPBR = string;
                    return stringLen;
                }
                if (i >= primLen){
                    *stringPBR = string;
                    break;
                }
            }
            if (primLen == 1) {
                if (i < primLen) {
                    string = realloc(string,sizeof(int)*(stringLen+1));
                    string[stringLen++] = closestNeck[i];
                }
                *stringPBR = string;
                return stringLen;
            }
            string = realloc(string,sizeof(int)*(stringLen+1));
            string[stringLen++] = closestNeck[i];
            // printf("%d",string[stringLen-1]);
        }
        // for (int i = 0;i<primLen;i++) printf("%d",closestNeck[i]);
        // printf("\n");
        greatestPCR3Below(closestNeck,n);
    }
    *stringPBR = string;
    return stringLen;
    //need to find the places to cut out.

    free(closestNeck);
}




// alpha gaurunteed to be an Alt necklace
int cutDownDB(int *alpha, int sizeCutDown, int n, int **stringPBR){
    // printf("%d",n);
    int *string = malloc(sizeof(int));
    int stringLen = 0;

    int rank = testRankDBseqPCR3(alpha,n);
    int diff = sizeCutDown-rank;
    // printf("diff: %d\n",diff);
    delArrBy1(alpha,n);
    if (diff == 0){
        stringLen = DB(alpha,n, &string);
        *stringPBR = string;
        // printString(string,stringLen);
        return stringLen;
    }
    int *cuts = malloc(sizeof(int));
    int sizeCuts = 1;
    if (diff > n/2){
        cuts[sizeCuts-1] = n/2;
        cuts = realloc(cuts,++sizeCuts*sizeof(int));
        diff = diff-n/2;
        if (diff > n/2 - 1){
            cuts[sizeCuts-1] = n/2-1;
            cuts = realloc(cuts,++sizeCuts*sizeof(int)); 
            diff = diff-(n/2-1);
        }
    }
    cuts[sizeCuts-1] = diff;
    for (int i =0;i<sizeCuts;i++){
        printf("%d\n",cuts[i]);
    }
    qsort(cuts,sizeCuts,sizeof(int),cmp);
    
    //need to find the strings that have substrings that are going to be cutout

    int currentCutLen;
    int (*cutLocations)[n] = calloc(sizeCuts, sizeof(*cutLocations));
    int *cutdownNecklacesRank = malloc(sizeof(int)*sizeCuts);
    for (int i =0;i<sizeCuts;i++){
        
        printf("%d\n",cuts[i]);
        currentCutLen = cuts[i];
        if (currentCutLen == 1){
            cutdownNecklacesRank[i] = n;
            continue;
        }
        for (int j=0;j<=n-currentCutLen;j++){
            if (j%currentCutLen == 0){
                cutLocations[i][j] = 1;
            }
        }
        cutdownNecklacesRank[i] = getRank(cutLocations[i],n);
    }
    // int curCutOut= 0;
    // int isCut = 0;
    // while (1) {
        // primLen = primLength(alpha,n);
        // if (getRank(alpha,n) == cutdownNecklacesRank[curCutOut]){
            // isCut = 1; 
            // printf("HERE");
        // }
        // delArrBy1(alpha,n);
        // for (int i =0;i<primLen;i++){
            // if (isCut){
                // i = i + cuts[curCutOut];
                // isCut=0; 
                // curCutOut++;
                // if (primLen == 1) {
                    // *stringPBR = string; 
                    // return stringLen;
                // }
                // if (i >= primLen){
                    // *stringPBR = string;
                    // break;
                // }
            // }
            // 
            // if (primLen == 1) {
                // if (i < primLen) {
                    // string = realloc(string,sizeof(int)*(stringLen+1));
                    // string[stringLen++] = alpha[i]+1;
                // }
                // *stringPBR = string;
                // return stringLen;
            // }
            // string = realloc(string,sizeof(int)*(stringLen+1));
            // string[stringLen++] = alpha[i];
        // }
        // greatestPCR3Below(alpha,n);
    // }
    // *stringPBR = string;
    // return stringLen;
}

int rankCutDownDB(int *neck, int *alpha, int sizeCutDown, int n){
    //set up some checks for the wraparound
    int *temp = malloc(sizeof(int)*n);
    temp[0] = 0;
    for (int i=0;i<n-1;i++) temp[i+1] = neck[i];
    for (int i=1;i<=n;i++){
        if (areArraysEqual(temp,alpha,n)){
            return i;
        }
        // for (int j=0;j<n;j++) printf("%d",temp[j]);
        // printf("\n");
        for (int j=n-2;j>=0;j--){
            temp[j+1] = temp[j];
        }
        temp[0] = 0;
    }



    int rank = testRankDBseqPCR3(neck,n);
    int diff = sizeCutDown-rank;
    // printf("%d %d",diff,rank);
    if (diff == 0){
        // printf("hello");
        return getRank(alpha,n);
    }
    int *cuts = malloc(sizeof(int));
    int sizeCuts = 1;
    if (diff > n/2){
        cuts[sizeCuts-1] = n/2 + 1;
        cuts = realloc(cuts,++sizeCuts*sizeof(int));
        diff = diff-n/2;
    }
    printf(".");
    
    cuts[sizeCuts-1] = diff;
    delArrBy1(neck,n);

    //finding Ranks of the cutouts
    int currentCutLen;
    int (*cutLocations)[n] = calloc(sizeCuts, sizeof(*cutLocations));
    int *cutdownNecklacesRank = malloc(sizeof(int)*sizeCuts);
    for (int i =0;i<sizeCuts;i++){
        currentCutLen = cuts[i];
        if (currentCutLen == 1){
            cutdownNecklacesRank[i] = n;
            continue;
        }
        for (int j=0;j<=n-currentCutLen;j++){
            if (j%currentCutLen == 0){
                cutLocations[i][j] = 1;
            }
        }
        cutdownNecklacesRank[i] = getRank(cutLocations[i],n);
    }

    int unCutRank = getRank(alpha,n);
    for (int i =0;i<sizeCuts;i++){
        if (unCutRank < cutdownNecklacesRank[i]+cuts[i]+ n%(cuts[i]) && unCutRank > cutdownNecklacesRank[i]+ n%(cuts[i])-1 ){
            printf("%d %d ",unCutRank,cutdownNecklacesRank[i]);
            printf("String does not exist\n");
            return -1;
        }
    }
    // for (int i =0;i<sizeCuts)
    for (int i =sizeCuts-1;i>=0;i--){
        if (unCutRank > cutdownNecklacesRank[i]+ n%(cuts[i])-1){
            unCutRank = unCutRank - cuts[i];
        }
        // else if (unCutRank > cutdownNecklacesRank[i]-cuts[i]){
        //     printf("String does not exist");
        //     return -1;
        // }
    }
    // delArrBy1(alpha,n);
    // printf("Rank: %d\n", unCutRank);

    // printf("\n");
    return unCutRank;
}

int newRankCutDownDB(int *alpha, int sizeCutDown){
    int n = (sizeCutDown == 0) ? 1 : 32 - __builtin_clz(sizeCutDown);
    int *closestNeck = malloc(sizeof(int)*n);
    sizeCutDown = (int)pow(2,n)- sizeCutDown;
    int unCutDBSeq = getClosestNeckInDBSeq(sizeCutDown,n,closestNeck);
    // for (int i=0;i<n;i++) printf("%d",closestNeck[i]);
    // printf("\n");
    int *string = malloc(sizeof(int));
    int diff = sizeCutDown-unCutDBSeq;
    // printf("\n");
    fflush(stdout);
    int *cuts = malloc(sizeof(int));
    int stringLen = 0;

     if (diff == 0){
        printf("0 diff");
        stringLen = DB(closestNeck,n, &string);
        int rankInFullDB = getRank(alpha,n);
        return rankInFullDB - (pow(2,n)-stringLen);
    }
    //the following code just gets all cuts and puts them in an array for easy access
    /***********************/
    int sizeCuts = 1;
    if (diff > (n+1)/2){
        cuts[sizeCuts-1] = (n+1)/2;
        cuts = realloc(cuts,++sizeCuts*sizeof(int));
        diff = diff-(n+1)/2;
    }
    cuts[sizeCuts-1] = diff;
    /***********************/
    qsort(cuts,sizeCuts,sizeof(int),cmp);


    //the following code will get all of the strings that will have values cut out of them
    /***********************/
    int currentCutLen;
    int (*cutLocations)[n] = calloc(sizeCuts, sizeof(*cutLocations));
    int *cutdownNecklacesRank = malloc(sizeof(int)*sizeCuts);
    for (int i =0;i<sizeCuts;i++){
        
        // printf("%d\n",string[i]);
        currentCutLen = cuts[i];
        if (currentCutLen == 1){
            cutdownNecklacesRank[i] = pow(2,n)-n;
            continue;
        }
        for (int j=0;j<=n-currentCutLen;j++){
            if (j%currentCutLen == 0){
                cutLocations[i][j] = 1;
            }
        }
        cutdownNecklacesRank[i] = getRank(cutLocations[i],n);
    }
    int curCutOut= 0;
    int isCut = 0;
    /***********************/

    int unCutRank = getRank(alpha,n);
    for (int i =0;i<sizeCuts;i++){
        if (unCutRank > cutdownNecklacesRank[i]-cuts[i]- n%(cuts[i]) && unCutRank < cutdownNecklacesRank[i]- n%(cuts[i]) ){
            printf("String does not exist\n");
            return -1;
        }
    }
    // for (int i =0;i<sizeCuts)
    for (int i =sizeCuts-1;i>=0;i--){
        if (unCutRank > cutdownNecklacesRank[i]- n%(cuts[i])-cuts[i]){
            unCutRank = unCutRank - cuts[i];
        }
    }
    // unCutRank = unCutRank - (pow(2,n)-stringLen);
    
    free(closestNeck);
    return unCutRank - unCutDBSeq;
    
}

void unrankCutDownDB(int *neck, int position, int sizeCutDown,int n, int *alpha){
    int *copy = malloc(sizeof(int)*n);
    for (int i =0;i<n;i++) copy[i] = neck[i];
    
    int rank = testRankDBseqPCR3(neck,n);
    int diff = rank-sizeCutDown;
    // printf("%d %d",diff,rank);
    if (diff == 0){
        // printf("hello");
        if (position < n){
            for (int i =0;i<position;i++) alpha[i] = 0;
            for (int i =0;i<n-position;i++) alpha[position+i] = copy[i];
            return;
        }
        unrank(position,n,alpha);
        return;
    }
    int *cuts = malloc(sizeof(int));
    int sizeCuts = 1;
    if (diff > n/2){
        // printf("proc, %d %d",diff, n/2);
        cuts[sizeCuts-1] = n/2;
        cuts = realloc(cuts,++sizeCuts*sizeof(int));
        diff = diff-n/2;
        if (diff > n/2 - 1){
            // printf("proc 2, %d %d", diff, (n/2)-1);
            cuts[sizeCuts-1] = n/2-1;
            cuts = realloc(cuts,++sizeCuts*sizeof(int)); 
            diff = diff-(n/2-1);
        }
    }
    // printf("sizeCuts: %d\n",sizeCuts);
    cuts[sizeCuts-1] = diff;
    delArrBy1(neck,n);
    //set up some checks for the wraparound
    if (position < n){
        // printf("\nCOPY");
        // for (int i =0;i<n;i++) printf("%d",copy[i]);
        // printf("\nCOPY");
        if (cuts[sizeCuts-1] == 1){
            for (int i =0;i<position-1;i++) alpha[i] = 0;
            for (int i =0;i<n-position;i++) alpha[position+i] = copy[i];
            return;
        }  
        for (int i =0;i<position;i++) alpha[i] = 0;
        for (int i =0;i<n-position;i++) alpha[position+i] = copy[i];
        return;
    }

    
    

    //finding Ranks of the cutouts
    int currentCutLen;
    int (*cutLocations)[n] = calloc(sizeCuts, sizeof(*cutLocations));
    int *cutdownNecklacesRank = malloc(sizeof(int)*sizeCuts);
    for (int i =0;i<sizeCuts;i++){
        currentCutLen = cuts[i];
        if (currentCutLen == 1){
            cutdownNecklacesRank[i] = n;
            continue;
        }
        for (int j=0;j<n-currentCutLen;j++){
            if (j%currentCutLen == 0){
                cutLocations[i][j] = 1;
            }
        }
        // for (int j=0;j<n;j++) printf("%d",cutLocations[i][j]);
        // printf("\n");
        cutdownNecklacesRank[i] = getRank(cutLocations[i],n);
    }
    // printf("diff: %d\n",diff);

    // for (int i =0;i<sizeCuts;i++){
    //     printf("cuts: %d, ranks: %d",cuts[i], cutdownNecklacesRank[i]);
    //     printf("\n");
    // }

    for (int i = 0;i < sizeCuts;i++){
        for (int j=0;j< sizeCuts;j++){
            if (cutdownNecklacesRank[j] > cutdownNecklacesRank[i]) cutdownNecklacesRank[j] = cutdownNecklacesRank[j] - cuts[i];
        }
        if (n%cuts[i] == 0) cutdownNecklacesRank[i] += cuts[i]-1;
    }

    // for (int i =0;i<sizeCuts;i++){
    //     printf("cuts: %d, ranks: %d",cuts[i], cutdownNecklacesRank[i]);
    //     printf("\n");
    // }
    int originalPosition = position;
    for (int i =sizeCuts-1;i>=0;i--){
        if (originalPosition > cutdownNecklacesRank[i] || cuts[i] == 1){
            position = position + cuts[i];
        }
    }
    unrank(position,n,alpha);
    return;
}

void newUnrankCutDownDB(int position, int sizeCutDown,int *strBPR){
    int n = (sizeCutDown == 0) ? 1 : 32 - __builtin_clz(sizeCutDown);
    int *closestNeck = malloc(sizeof(int)*n);
    sizeCutDown = (int)pow(2,n)- sizeCutDown;
    int unCutDBSeq = getClosestNeckInDBSeq(sizeCutDown,n,closestNeck);
    // for (int i=0;i<n;i++) printf("%d",closestNeck[i]);
    // printf("\n");
    int *string = malloc(sizeof(int));
    int diff = sizeCutDown-unCutDBSeq;
    // printf("\n");
    position += (unCutDBSeq);
    int *cuts = malloc(sizeof(int));
    int stringLen = 0;

     if (diff == 0){
        stringLen = DB(closestNeck,n, &string);
        unrank(position,n,strBPR);
        return;
    }
    //the following code just gets all cuts and puts them in an array for easy access
    /***********************/
    int sizeCuts = 1;
    if (diff > (n+1)/2){
        cuts[sizeCuts-1] = (n+1)/2;
        cuts = realloc(cuts,++sizeCuts*sizeof(int));
        diff = diff-(n+1)/2;
    }
    cuts[sizeCuts-1] = diff;
    /***********************/
    qsort(cuts,sizeCuts,sizeof(int),cmp);
    printf("cuts: ");
    for (int i =0;i<sizeCuts;i++){
        printf(" %d ",cuts[i]);
    }


    //the following code will get all of the strings that will have values cut out of them
    /***********************/
    int currentCutLen;
    int (*cutLocations)[n] = calloc(sizeCuts, sizeof(*cutLocations));
    int *cutdownNecklacesRank = malloc(sizeof(int)*sizeCuts);
    for (int i =0;i<sizeCuts;i++){
        
        // printf("%d\n",string[i]);
        currentCutLen = cuts[i];
        if (currentCutLen == 1){
            cutdownNecklacesRank[i] = pow(2,n)-n;
            continue;
        }
        for (int j=0;j<=n-currentCutLen;j++){
            if (j%currentCutLen == 0){
                cutLocations[i][j] = 1;
            }
        }
        cutdownNecklacesRank[i] = getRank(cutLocations[i],n);
    }
    int curCutOut= 0;
    int isCut = 0;
    /***********************/

    for (int i = 0;i < sizeCuts;i++){
        for (int j=0;j< sizeCuts;j++){
            if (cutdownNecklacesRank[j] > cutdownNecklacesRank[i] && cuts[i] != 1) cutdownNecklacesRank[j] = cutdownNecklacesRank[j] - cuts[i];
        }
        if (n%cuts[i] == 0) cutdownNecklacesRank[i] -= cuts[i];
    }

    // for (int i =0;i<sizeCuts)
    for (int i =sizeCuts-1;i>=0;i--){
        if (position > cutdownNecklacesRank[i]- n%(cuts[i])-cuts[i] && cuts[i] != 1){
            printf("%d %d",n%(cuts[i]),cuts[i]);
            position = position + cuts[i];
        }
    }
    printf(" %d %d",position-unCutDBSeq,position);
    // unCutRank = unCutRank - (pow(2,n)-stringLen);
    unrank(position,n,strBPR);
    free(closestNeck);
    return;
}