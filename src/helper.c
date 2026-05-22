#include "../inc/helper.h"

#define k 2

void displayString(int* string,int n){
    for (int i =0;i<n;i++) {printf("%d",string[i]);}
    printf("\n");
}


int *compute_lps(const int arr[], int n) {
    int *lps = calloc(n, sizeof(int));
    if (lps == NULL) return NULL;

    int len = 0;

    for (int i = 1; i < n; i++) {
        while (len > 0 && arr[i] != arr[len]) {
            len = lps[len - 1];
        }

        if (arr[i] == arr[len]) {
            len++;
        }

        lps[i] = len;
    }

    return lps;
}

int shortest_repeating_length(const int arr[], int n) {
    if (n <= 0) return 0;

    int *lps = compute_lps(arr, n);
    if (lps == NULL) return -1;

    int longest_border = lps[n - 1];
    int period = n - longest_border;

    free(lps);

    if (n % period == 0) {
        return period;
    }

    return n;
}

int isArrayBigger(int *arr1, int *arr2, int n) {
    for (int i = 0; i < n; ++i) {
        if (arr1[i] > arr2[i]) return 1;
        if (arr1[i] < arr2[i]) return 0;
    }
    return 0; // arrays are equal
}



int binToNum(int *ptr, int n){
    int sum = 0;
    for (int i=0;i<n;i++){
        sum += ptr[i]*pow(2,n-i-1);
    }
    return sum;
}

void numToBin(int num, int len, int *ptr){
    for (int i=len-1;i>=0;i--){
        ptr[i] = num%2;
        num = num/2;
    }
}


void PCR1ToPCR3(int alpha[], int n){
    int i;
    for (i=0;alpha[i]== 0;i++){}
    for (int j=0;j<n-i;j++){
        alpha[j] = alpha[j+i];
    }
    for (int j=n-1;j>n-1-i;j--){
        alpha[j] = 0;
    }
}

void PCR3ToPCR1(int alpha[], int n){
    int i;
    int dum[n];
    for (int j=0;j<n;j++){
        dum[j] = alpha[j];
    }
    for (i=0;alpha[n-i-1]==0;i++){}
    for (int j=0;j<n-i;j++){
        alpha[j+i] = dum[j];
    } 
    for (int j=0;j<i;j++){
        alpha[j] = 0;
    }

}

int sumWeight(int alpha[], int len) {
    int weight = 0;
    for (int i = 0; i < len; i++) {
        weight = weight + alpha[i];
    }
    return weight;
}

int isNecklacePCR1(int *arr, int n) {
    if (n==1){return 1;}
    for (int shift = 1; shift < n; ++shift) {
        int is_smaller = 0;
        for (int i = 0; i < n; ++i) {
            int a = arr[i];
            int b = arr[(i + shift) % n];
            if (a < b) break;
            if (a > b) { is_smaller = 1; break; }
        }
        if (is_smaller) return 0;
    }
    return 1;
}

int isNecklacePCR3(int *arr, int n) {
    int sum = 0;
    for (int i=0;i<n;i++){
        sum += arr[i] * pow(2,i);
    }
    if (sum == 0 || sum == pow(2,n)-1) return 1;
    if (arr[0] == 0 || arr[n-1] == 1) return 0;
    int *dum;
    int numzero = 0;

    dum = malloc(sizeof(int)*n);
    for (int i=0;i<n;i++){
        dum[i] = arr[i];
    }

    while (dum[n-1-numzero] == 0){
        numzero++;
    }
    for (int i=0;i<n-numzero;i++){
        dum[i+numzero] = arr[i];
    }
    for (int i=0;i<numzero;i++){
        dum[i] = 0;
    }
    
    if (isNecklacePCR1(dum,n)) {
        for (int i=0;i<n;i++){
            // printf("%d", arr[i]);
        }
        // printf(" ");
        for (int i=0;i<n;i++){
            // printf("%d", dum[i]);
        }
        // printf("\n");
        free(dum);
        return 1;
    } else {
        free(dum);
    }
    return 0;
}



bool is_zeros_then_ones(const int arr[], int n, int *numZeros) {
    *numZeros = 0;

    // count leading 0s
    while (*numZeros < n && arr[*numZeros] == 0) {
        (*numZeros)++;
    }
    // remaining entries must all be 1
    for (int i = *numZeros; i < n; i++) {
        if (arr[i] != 1) {
            return false;
        }
    }
    
    if (arr[0] == 1) *numZeros = pow(2,n);
    return true;
}

int primLength(const int *a, int n){
    if(n <= 0) return 0;
    int *pi = (int*)malloc(n * sizeof(int));
    if(!pi) return n; // fallback
    pi[0] = 0;
    for(int i = 1; i < n; ++i){
        int j = pi[i-1];
        while(j > 0 && a[i] != a[j]) j = pi[j-1];
        if(a[i] == a[j]) ++j;
        pi[i] = j;
    }
    int p = n - pi[n-1];
    free(pi);
    return (n % p == 0) ? p : n;
}

void sumArrBy1(int *arr,int n){
    for (int i=0;i<n;i++){arr[i]++;}
}

void findNextGreatestNecklace(int string[], int n){
    int startOfRightmostStringOfOnes = -1;
    for (int i = n-1;i>=0;i--){
        if (string[i] == 1 && string[i-1] == 0){startOfRightmostStringOfOnes = i;break;}
    }
    if (string[0] == 0){
        string[0] = 1;
        for (int i = 1;i<n;i++){string[i] = 0;}
        return;
    }
    
    if (isNecklacePCR3(string,n)){return;}

    int iteratorOne = startOfRightmostStringOfOnes-1;
    string[iteratorOne] = 1;
    for (int i = startOfRightmostStringOfOnes;i<n;i++){string[i] = 0;}
    while (!isNecklacePCR3(string,n)){
        iteratorOne--;
        if (string[iteratorOne] == 1){continue;}
        string[iteratorOne] = 1;
        for (int i =iteratorOne+1;i<n;i++){string[i] = 0;}
        // for (int i =0;i<n;i++){printf("%d",string[i]);}
        // printf("  ");
    }
    return;
}

int smallestPCR3StrictlyAbove(int *alpha, int n){
    int *out = malloc(sizeof(int)*n);
    int foundFirstZero=0;
    memcpy(out, alpha, n* sizeof(int));
    if (isNecklacePCR3(out,n)){memcpy(alpha,out,n*sizeof(int));return 1;}
    for (int i = 1;i<=n;i++){
        if (!foundFirstZero){
            if (out[n-i] == 1){ 
                continue; //this finds the first time from the left side we find a zero
            } else {
                out[n-i] = 1; //this switches the first zero to a one
                for (int j=1;j<i;j++){out[n-i+j] = 0;} // this switches everything after the first zero to a 0
                foundFirstZero = 1;
            }
        }
        if (isNecklacePCR3(out,n) && isArrayBigger(out,alpha,n)){memcpy(alpha,out,n*sizeof(int));return 1;} //checking it its a necklace
        else {
            // printf("BURH");
            //this keeps moving the one to the left until it lands on a necklace. 
            out[n-i] = 1;
            out[n-i+1] = 0;
        }
    }
    
    return -1;
}

// Returns the number of unique rotations for a given necklace (array of length n)
int countUniqueRotationsPCR3(int *arr, int n) {
    int count = 0;
    for (int shift = 0; shift < n; ++shift) {
        int is_new = 1;
        for (int prev = 0; prev < shift; ++prev) {
            int same = 1;
            for (int i = 0; i < n; ++i) {
                if (arr[(i + shift) % n] != arr[(i + prev) % n]) {
                    same = 0;
                    break;
                }
            }
            if (same) { is_new = 0; break; }
        }
        if (is_new) count++;
    }
    return count;
}

void greatestPCR3Below(int *alpha, int n){
    // memcpy(out, alpha, n * sizeof(int));
    for (int i = n-1;i>=0;i--){
        if (alpha[i] == 0) {
            alpha[i] = 1;
        }
        else if (alpha[i] == 1) {
            alpha[i]=0;
            break;
        }
    }
    for (int i =1;i<=n;i++){
        alpha[n-i] = 0;
        if (isNecklacePCR3(alpha,n)){return;}
    }
}