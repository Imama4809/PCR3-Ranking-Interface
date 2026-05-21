#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../inc/DBseqPCR3.h"
#include "../inc/helper.h"
#include "../inc/PCR1NeckAndLyndon.h"
#include "../inc/PCR3NeckAndLyndon.h"

int main(){
    // int arr[] = {1,1,0,0,0,0};
   // for (int n=0;n<=15;n++){
    // printf("here%d\n",n);
    int n = 8;
    int twoPowN = pow(2,n);
    // int arr[] = {2,2,1,1,1,2,2,2,2,2,2,2,2,2,2,2};
    // int AArr[100][100]; 
    // int a[n];
    // int total;
    // int dum[n];
    // int necklaces = 0;

    int *ptr;
    int *dbsq;
    int oldLen = 0;

    int rot;
    for (int j=pow(2,n)-1;j>=0;j--){
        ptr = malloc(sizeof(int)*n);
        
        numToBin(j,n,ptr);
        // for (int i=0;i<n;i++){
        //     ptr[i]++;
        // }
        if (isNecklacePCR3(ptr,n)){

            rot = countUniqueRotationsPCR3(ptr,n);

            if (j==pow(2,n)-1) {
                oldLen = 1;
                dbsq = malloc(sizeof(int)*1);
            }
            else {
                oldLen +=rot;
                dbsq = realloc(dbsq,oldLen*sizeof(int));
            }
            for (int i=0;i<rot;i++){
                dbsq[oldLen-rot+i] = ptr[i];
                // printf("%d",dbsq[oldLen+i]);
            }
            // printf("  ");
            // printf("\n");
        }
        free(ptr);
    }   
    for (int i =0;i<oldLen;i++){
        printf("%d",dbsq[i]);
    }

    int *arr = malloc(sizeof(int)*n);
    int *arr2 = malloc(sizeof(int)*n);
    int pos = 0;
    int pos2 = 0;
    for (int j = 0;j< pow(2,n);j++){
        unrank(j,n,arr);
        // unrankNecklace(j,n,arr2);
        // for (int i =0;i<n;i++){
        //     if (arr[i] != arr2[i]) printf("%d %d\n",pos, j);
        // }
        // unrank(j,n,arr);
        // // for (int i =0;i<n;i++)printf("%d", arr[i]);
        pos2 = getRank(arr,n);
        if (j != pos2)
            printf("\n%d %d",j,pos2);
        // unrank(50,n,arr, &pos);
        // for (int i =0;i<n;i++)printf("%d", arr[i]);
        // printf("\n%d",pos);
        // unrank(20,n,arr, &pos);
        // for (int i =0;i<n;i++)printf("%d", arr[i]);
        // printf("\n%d",pos);
    }
    
}
