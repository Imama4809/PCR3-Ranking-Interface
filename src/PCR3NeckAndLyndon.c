#include "../inc/PCR3NeckAndLyndon.h"
#include "../inc/helper.h"

int PCR3CountN(int arr[], int n){
    int dum[n];
    int subt[n];
    int total = 0;
    if (arr[0] == 1) return 1;
    for (int i=0;i<n;i++){
        for (int j=0;j<i;j++){
            dum[j] = 1;
        }
        for (int j=i;j<n;j++){
            dum[j] = arr[j-i];
        }
        for (int j=0;j<=i;j++){
            subt[j] = 1;
        }
        for (int j=i+1;j<n;j++){
            subt[j] = 2;
        }

        total += N(n,0,dum) - N(n,0,subt);
    }
    total++;
    return total;
}


int PCR3CountL(int arr[], int n){
    int dum[n];
    int subt[n];
    int total = 0;
    if (arr[0] == 1) return 1;
    for (int i=0;i<n;i++){
        for (int j=0;j<i;j++){
            dum[j] = 1;
        }
        for (int j=i;j<n;j++){
            dum[j] = arr[j-i];
        }
        for (int j=0;j<=i;j++){
            subt[j] = 1;
        }
        for (int j=i+1;j<n;j++){
            subt[j] = 2;
        }
        total += L(n,0,dum) - L(n,0,subt);
    }
    total++;
    return total;
}


int PCR3Count(int arr[], int n){
    int dum[n];
    int subt[n];
    int total = 0;
    if (arr[0] == 1) return 0;
    for (int i=0;i<n;i++){
        for (int j=0;j<i;j++){
            dum[j] = 1;
        }
        for (int j=i;j<n;j++){
            dum[j] = arr[j-i];
        }
        for (int j=0;j<=i;j++){
            subt[j] = 1;
        }
        for (int j=i+1;j<n;j++){
            subt[j] = 2;
        }
        GreatestNecklaceSmallerThan(dum,n);
        for (int l=1;l<=n;l++){
            if (n%l==0) {total += ((L(n/l,0,dum) - L(n/l,0,subt))*(n/l));}            
        }
        
    }
    total++;
    return total;
}


int PCR3CountNew(int arr[], int n){
    int dum[n];
    int subt[n];
    int subt2[n];
    int total = 0;
    int othTotal= 0;
    if (arr[0] == 1) return pow(2,n);
    int t = 0;
    for (int i=0;i<n;i++){t+= arr[i];}
    if (t== 2*n) return 0;
    for (int i=0;i<n;i++){
        for (int j=0;j<i;j++){
            dum[j] = 1;
        }
        for (int j=i;j<n;j++){
            dum[j] = arr[j-i];
        }
        for (int j=0;j<i;j++){
            subt2[j] = 1;
        }
        for (int j=i;j<n;j++){
            subt2[j] = 2;
        }
        GreatestNecklaceSmallerThan(dum,n);
        // if (isNecklacePCR3(dum,n)) {GreatestNecklaceSmallerThan(dum,n);}
        for (int l=1;l<=n;l++){
            if (n%l==0) {
                total += ((L(n/l,0,subt2) - L(n/l,0,dum))*(n/l));
            }            
        }
        
    }
    return total;
}