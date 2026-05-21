// #include "common.c"
#include "../inc/helper.h"
#include "../inc/PCR1NeckAndLyndon.h"
#include <stdlib.h>

int sumWeightFirstJ(int alpha[], int j) {
    /*
    This function calculates the sum of the digits in the first j elements of alpha

    returns: sum of the first j digits
    */
    int weight = 0;
    for (int i = 0; i < j; i++) {
        weight = weight + alpha[i];
    }
    return weight;
}

int checkPreSuf(int alpha[],int pre1,int pre2,int suf1){
    /*
    This function checks if the prefix from pre1 to pre2, it the same as suf1 to whatever ends at the same length

    returns: 1 if true, 0 if false
    */
    for (int i=0;i<pre2-pre1;i++){
        if (alpha[pre1+i] != alpha[suf1+i]){
            //if there are two indexes that are not equal we return a false value. 
            return 0;
        }
    }
    //this only goes through if all the indexes are equal
    //note if pre2 == pre1 then this will also return true. 
    return 1;
}

int findLargestS(int alpha[], int j, int t, int n){
    /*
    This value looks through alpha and finds the largest suffix of alpha[1,t-1] and tries to find the largest suffix
    that is equal to the equivalent sized prefix of alpha

    returns: size of the largest suffix 
    */
    int largestS = 0;
    for (int i=1;i<=j-(n-t+1);i++){
        //looks through the first j-(n-t+1) elements of alpha.
        if (checkPreSuf(alpha,j-i,j,0)){
            //looks for longest suffix
            largestS = i;
        }
    }
    return largestS;
}

int S(int n, int w, int **tableS) {
    /*
    This function calculates how many possible strings of length n with weight greater than or equal to w

    returns: the number of strings of length n with weight greater than or equal to alpha
    */

    if ((n==0 && w>0) || w >k*n){
        return 0;
    }
    if (w<=0){
        return pow(k,n);
    }


    if (tableS[n][w] != -1) {
        return tableS[n][w];
    } else {
        int total = 0;
        for (int i = 1; i <= k; i++) {
            total += S(n - 1, w - i, tableS);
        }
        tableS[n][w] = total;
        return tableS[n][w];
    }
}

int xS(int n, int w, int j, int **tableS){
    /*
    This function calculates how many strings there are of length n with weight greater than or equal to w with the 
    restriction that j is the maximum that the first digit is allowed to be

    returns: count of strings of length n with weight greater than or equal to w given j is the max the first digit
    is allowed to be 
    */
    int total = 0;
    for (int i=1;i<j && i <= k;i++){
        //If line establishes that if the min weight goes below zero, its the same as being 0. 
        total += S(n-1,w-i,tableS);
    }
    return total;
}

int B(int t, int j, int w, int alpha[], int ***tableB) {
    /*
    This function calculates the number of strings that have weight less than or equal to w and all possible substrings
    are lex greater than alpha

    returns: number of strings that have weight less than or equal to to w and all possible substrings are lex greater 
    than alpha
    */
    int total=0;
    int WinJ = 0;
    if (w<0){
        w=0;
    }
    if (t==0 && j==0 && w==0){
        return 1;
    }
    if (t==0 && j==0 && w>0){
        return 0;
    }
    if (tableB[t][j][w] == -1){
        for (int i = 0; i < j; i++) {
            WinJ = WinJ + alpha[i] ;
        }
        total += B(t, j + 1, w, alpha, tableB);
        for (int q = alpha[j] +1; q <= k; q++) {
            total += B(t - j - 1, 0, w - q - WinJ, alpha, tableB);
        }
        tableB[t][j][w] = total;
    } else {
        total = tableB[t][j][w];
    }
    return tableB[t][j][w];
}

int P(int t, int j, int w, int alpha[], int ***tableP) {
    /*
    This function calculates the number of strings that have weight equal to w and all possible substrings are lex 
    greater than alpha

    returns: number of strings that have weight equal to w and all possible substrings are lex greater than alpha
    */
    int total=0;
    int WinJ = 0; //Weight within the range of 1 to J
    if (t < 0 || j < 0 || w < 0) {
        return 0;
    }
    if (t==0 && j==0 && w==0){
        return 1;
    }

    if (t==0 && j==0 && w!=0){
        return 0;
    }

    if (tableP[t][j][w] == -1){
        for (int i = 0; i < j; i++) {
            WinJ = WinJ + alpha[i] ;
        }
        total += P(t, j + 1, w, alpha, tableP);
        for (int q = alpha[j] +1;q <= k; q++) {
            total += P(t - j - 1, 0, w - q - WinJ, alpha, tableP);
        }
        tableP[t][j][w] = total; // Store the result in the table
    } else {
        total = tableP[t][j][w];
    }
    return tableP[t][j][w];
}



int minPeriod(const int *arr, int n) {
    if (n <= 0) return 0;

    int *pi = (int*)malloc(n * sizeof(int));
    pi[0] = 0;
    for (int i = 1; i < n; ++i) {
        int j = pi[i-1];
        while (j > 0 && arr[i] != arr[j]) j = pi[j-1];
        if (arr[i] == arr[j]) ++j;
        pi[i] = j;
    }
    int p = n - pi[n-1];
    int ans = (n % p == 0) ? p : n;
    free(pi);
    return ans;
}


int A(int n, int t, int j, int w, int alpha[], int ***tableB, int ***tableP, int **tableS){
    /*
    This function calculates the number of strings that have its first rotation smaller than alpha after t-1 rotations 
    and copies the first j elements of alpha

    returns: number of strings whose first rotation is less than alpha is at t-1 rotations and copies the first j elements
    of alpha
    */


    


    int total = 0;
    int s;
    int w1 = w - sumWeightFirstJ(alpha, j);

    int totalWeight = sumWeightFirstJ(alpha,n);

    if (n==j){
        if (totalWeight >=w && t<= minPeriod(alpha,n)) return 1;
        return 0;
    }
    if (t+j  <= n){
        for (int q=0;q<=k*(t-1);q++){ 
            total += P(t-1,0,q,alpha,tableP)*(xS(n-t-j+1, 0> w1-q ? 0: w1-q ,alpha[j],tableS));
        }
    }
    else {
        s = findLargestS(alpha,j,t,n);
        if (alpha[s] < alpha[j]){
            total += B(n-j+s,s+1,w1+sumWeightFirstJ(alpha,s),alpha,tableB);
        }
        for (int i=alpha[s]+1;i<alpha[j];i++){
            total += B(n-j-1,0, w1 + sumWeightFirstJ(alpha,s)-i,alpha,tableB);
        }
    }
    return total;
}


int T(int n, int w, int alpha[]){
    /*
    This function goes through all the possible values for inputs of the function A with a fixed weight W, essentially 
    counting the amount of strings of length n that have a necklace representation less than alpha.

    returns : strings of length n that have a necklace rep. less than alpha
    */

    // initalizing the arrays
    int ***tableB;
    int ***tableP;
    int **tableS;
    tableB = (int***) malloc(sizeof(int**)*(n+1));
    tableP = (int***) malloc(sizeof(int**)*(n+1));
    tableS = (int**) malloc(sizeof(int*)*(n+1));
    for (int i=0;i<n+1;i++){
        tableB[i] = (int**) malloc(sizeof(int*)*(n+1));
        tableP[i] = (int**) malloc(sizeof(int*)*(n+1));
        tableS[i] = (int*) malloc(sizeof(int)*(k*n+1));
        for (int j=0;j<n+1;j++){
            tableB[i][j] = (int*) malloc(sizeof(int)*(k*n+1));
            tableP[i][j] = (int*) malloc(sizeof(int)*(k*n+1));
        }
    }

    for (int j = 1;j<n*k+1; j++) {
        tableS[0][j] = 0; // There's is no way to form a string of length 0 with weight greater than or equal to j
    }
    for (int i = 1; i < n+1; i++) {
        for (int j = 0; j < k*n+1; j++) {
            tableS[i][j] = -1; // Initialize the table with -1
            if (j > pow(k,i)){
                tableS[i][j] = 0; // If j is greater than the maximum weight for n, set to 0
            }
            if (j==0){
                tableS[i][j] = pow(k,i); // There are q-1 to the power i strings of length i with weight >=0
            }
        }
    }
    tableS[0][0] = 1;
    for (int i=0;i<n+1;i++){
        for (int j=0;j<n+1;j++){
            for (int l=0;l<k*n+1;l++){
                tableB[i][j][l] = -1;
                tableP[i][j][l] = -1;
            }
        }
    }
    for (int t=0;t<n+1;t++){
        for (int i=0;i<k*n+1;i++){
            tableB[t][t][i] = 0;
        }
    }
    tableB[0][0][0] = 1; // Base case: B(0, 0, 0) = 1

    for (int t=1;t<n+1;t++){
        for (int i=0;i<k*n+1;i++){
            tableP[t][t][i] = 0;
        }
    }
    tableP[0][0][0] = 1; // Base case: P(0, 0, 0) = 1

    int totalStrings = 0;
    for (int t = 1; t <= n; t++) {
        for (int j = 0; j <= n; j++) {
            totalStrings += A(n, t, j, w, alpha,tableB,tableP,tableS);
            // printf("%d ", A(n, t, j, w, alpha,tableB,tableP,tableS));
        }
        // printf("\n");
        // printf(".  %d.  \n", totalStrings);
    }
    // printf("\n\n%d",totalStrings);
    for (int i=0;i<n+1;i++){
        for (int j=0;j<n+1;j++){
            free(tableB[i][j]);
            free(tableP[i][j]);
        }
        free(tableB[i]);
        free(tableP[i]);
        free(tableS[i]);
    }
    free(tableB);
    free(tableP);
    free(tableS);
    return totalStrings;
}



//USED FOR PHI

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

//USED FOR N 

int isGreater(int *arr, int *alpha, int n) {
    for (int i = 0; i < n; ++i) {
        if (arr[i] > alpha[i]) return 1;
        if (arr[i] < alpha[i]) return 0;
    }
    return 1; // equal
}

// Finds the next largest necklace above alpha (lex order)
int GreatestNecklaceSmallerThan(int *alpha, int n) {
    if (isNecklacePCR1(alpha,n)){
        return 1;
    }
    int *arr;
    arr = (int*) malloc(n * sizeof(int));
    memcpy(arr, alpha, n * sizeof(int));
    while (1) {
        // Increment lexicographically
        int i = n - 1;
        while (i >= 0 && arr[i] == 1) {
            arr[i] = k;
            i--;
        }
        if (i < 0) {free(arr);return 0;} // No larger string exists
        arr[i]--;
        // Check if it's a necklace and greater than alpha
        if (isNecklacePCR1(arr, n)) {
            memcpy(alpha, arr, n * sizeof(int));
            free(arr);
            return 1;
        } 
    }
    
}


int phi(int n){
    int value = 0;
    if (n == 1) {
        return 1; // phi(1) = 1
    }
    for (int i = 1; i < n; i++) {
        if (gcd(n, i) == 1) {
            value++;
        }
    }
    return value;
}
int mu(int n) {
    if (n == 1) return 1;
    int count = 0;
    for (int p = 2; p * p <= n; ++p) {
        if (n % p == 0) {
            n /= p;
            count++;
            if (n % p == 0) return 0;  // squared prime factor
        }
        while (n % p == 0) n /= p;
    }
    if (n > 1) count++;               // remaining prime factor
    return (count % 2 == 0) ? 1 : -1;
}

int N(int n, int w, int alpha[]){
    int *result;
    int total = 0;
    // int alpha[n];
    // for (int i = 0;i<n;i++){alpha[i] = alpha1[i];}
    GreatestNecklaceSmallerThan(alpha,n);
    for (int i=1;i<=n;i++){
        if (n%i == 0){
            result = (int *) malloc(n/i * sizeof(int));
            for (int j=0;j<n/i;j++){
                result[j] = alpha[j];
            }
            // if (i!=1 || !isNecklace(alpha,n)){
            GreatestNecklaceSmallerThan(result, n/i);
            // printf("\n");
            // printf("\n");
            // }
            // printf("%d, %d\n", T(n/i,w/i,result),phi(i));
            total += T(n/i, w/i, result) * phi(i);
            // printf("\n%d %d %d \n", T(n/i,w/i,result), phi(i), i);
            free(result);
        }
    }
    return total/n;
}


int L(int n, int w, int alpha1[]){
    int alpha[n];
    for (int i = 0;i<n;i++){alpha[i] = alpha1[i];}
    int *result;
    int total = 0;
    // GreatestNecklaceSmallerThan(alpha,n);
    GreatestNecklaceSmallerThan(alpha,n);
    // for (int i=0;i<n;i++){printf("%d",alpha[n]);}
    // printf("\n");
    for (int i=1;i<=n;i++){
        if (n%i == 0){
            result = (int *) malloc(n/i * sizeof(int));
            for (int j=0;j<n/i;j++){
                result[j] = alpha[j];
            }
            // if (i!=1 || !isNecklace(alpha,n)){
            GreatestNecklaceSmallerThan(result, n/i);
            // printf("\n");
            // printf("\n");
            // }
            // printf("%d, %d\n", T(n/i,w/i,result),phi(i));
            total += T(n/i, w/i, result) * mu(i);
            // printf("\n%d %d %d \n", T(n/i,w/i,result), phi(i), i);
            free(result);
        }
    }
    return total/n;
}

