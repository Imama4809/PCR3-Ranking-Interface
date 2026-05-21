#include "../inc/PCR3NeckAndLyndon.h"

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
        // for (int j=1;j<=n;j++){
            // if (n%j==0) {
                // for (int l = n/j;l>0;l--){
                    // total += (L(n/j,0,dum) - L(n/j,0,subt))*n/j;
                    total += N(n,0,dum) - N(n,0,subt);
                // }
                // printf("(%d - %d) * %d",L(n/j,0,dum),L(n/j,0,subt),n/j);
            // }
        // }
        
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
        // N(n,0,dum)-N(n,0,subt);
        for (int l=0;l<=n;l++){
            
            if (n%l==0) {
                // printf("\n");
                // for (int m = 0;m<n/l;m++){printf("%d",dum[m]);}
                // printf(" - ");
                // for (int m = 0;m<n/l;m++){printf("%d",subt[m]);}
                // for (int l = n/j;l>0;l--){
                    total += ((L(n/l,0,dum) - L(n/l,0,subt))*n/l);
                    // total += N(n/j,0,dum);
                // }
                
                // printf("  * %d, ",L(n/l,0,dum) - L(n/l,0,subt));
            }
            
        }
        // total++;
        
    }
    total++;
    return total;
}
