#include "../inc/interface.h"

void textInterface(){
    //options 
    // 1 rank PCR3 necklace
    // 2 rank PCR3 Lyndon Word
    // 3 unrank PCR3 necklace
    // 4 rank DB seq PCR3
    // 5 unrank DB seq PCR3
    int n, option;
    
    // n=8;
    printf("pick an option\n");
    printf("1: rank PCR3 necklace\n");
    printf("2: rank PCR3 Lyndon Word\n");
    printf("3: find closest PCR3 necklace from rank\n");
    printf("4: rank find DB seq PCR3\n");
    printf("5: unrank DB seq PCR3\n");
    printf("6: print DB sequence of size n\n");
    printf("7: print cutdown DB sequence\n");
    printf("8: rank cutdown DB sequence\n");
    printf("9: unrank cutdown DB sequence\n");
    printf("option: ");
    scanf("%d",&option);
    switch (option){
        case 1: {
            printf("\nwhat size of string (n value)?: ");
            scanf("%d",&n);
            int *alpha = malloc(sizeof(int) * n);
            char buf[128];
            printf("input your string (0s and 1s only): ");
            scanf("%s", buf);
            for (int i = 0; i < n; i++) {
                alpha[i] = buf[i] - '0';
            }
            printf("rank: %d\n",testRankNecklacePCR3(alpha,n));
            free(alpha);
            break;
        }
        case 2: {
            printf("\nwhat size of string (n value)?: ");
            scanf("%d",&n);
            int *alpha = malloc(sizeof(int) * n);
            char buf[128];
            printf("input your string (0s and 1s only): ");
            scanf("%s", buf);
            for (int i = 0; i < n; i++) {
                alpha[i] = buf[i] - '0';
            }
            printf("rank: %d\n",testRankLyndonWordPCR3(alpha,n));
            free(alpha);
            break;
        }
        case 3: {
            printf("\nwhat size of string (n value)?: ");
            scanf("%d",&n);
            int rank;
            printf("input your rank: ");
            scanf("%d",&rank);
            int *neck = testGetClosestNeckInDBSeqPCR3(rank,n);
            printf("string: ");
            for (int i=0;i<n;i++){
                printf("%d",neck[i]);
            }
            printf("\n");
            free(neck);
            break;
        }
        case 4: {
            printf("\nwhat size of string (n value)?: ");
            scanf("%d",&n);
            int *alpha = malloc(sizeof(int) * n);
            char buf[128];
            printf("input your string (0s and 1s only): ");
            scanf("%s", buf);
            for (int i = 0; i < n; i++) {
                alpha[i] = buf[i] - '0';
            }
            printf("rank: %d\n", testRankDBseqPCR3(alpha, n));
            free(alpha);
            break;
        }
        case 5: {
            printf("\nwhat size of string (n value)?: ");
            scanf("%d",&n);
            int rank;
            printf("input your rank: ");
            scanf("%d",&rank);
            int *string = testUnrankDBseqPCR3(rank,n);
            printf("string: ");
            for (int i=0;i<n;i++){
                printf("%d",string[i]);
            }
            printf("\n");
            free(string);
            break;
        }
        case 6:{
            printf("\nwhat size of string (n value)?: ");
            scanf("%d",&n);
            printf("DB sequence: ");
            printf("%d",1);
            int *string = malloc(sizeof(int)*n);
            for (int i =0;i<n-1;i++) string[i] = 1;
            string[n-1]=0;
            DB(string,n);
            // for (int i =0;i<n;i++) printf("0");
            printf("\n");
            free(string);
            break;
        }
        case 7:{
            int sizeCutDown;
            printf("\nwhat size of cut down DB sequence?: ");
            scanf("%d",&sizeCutDown);
            n = 31 - __builtin_clz(sizeCutDown)+1;
            int *neck = testGetClosestNeckInDBSeqPCR3(sizeCutDown,n);
            // printf("%d %d", n, sizeCutDown);
            if ((1 << n) == sizeCutDown) {
                for (int i=0;i<n;i++) neck[i]=1;
                printf("%d",1);
                neck[n-1] = 0;
                DB(neck,n);
                printf("\n");
                return;
            } else if ((1 << n) - 1 == sizeCutDown) {
                for (int i=0;i<n;i++) neck[i]=1;
                printf("%d",1);
                neck[n-1] = 0;
                DB(neck,n);
                printf("\n");
                return;
            } else if ((1 << n) - 2 == sizeCutDown){
                for (int i=0;i<n;i++) neck[i]=1;
                printf("%d",1);
                neck[n-1] = 0;
                int *cuts = malloc(sizeof(int));
                cuts[0] = 2;
                cutDownDB(neck,cuts,1,n);
                printf("\n");
                return;
            }

            int rank = testRankDBseqPCR3(neck,n);
            int diff = rank-sizeCutDown;
            delArrBy1(neck,n);
            if (diff == 0){
                DB(neck,n);
                return;
            }
            // printf("rank: %d\n",rank);
            // printf("diff: %d\n",diff);
            // printf("n: %d\n",n);
            int *cuts = malloc(sizeof(int));
            // printf("\n");
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
            // for (int i =0;i<sizeCuts;i++){
            //     printf("cut: %d\n", cuts[i]);
            // }
            cutDownDB(neck,cuts,sizeCuts,n);
            // printf("\n");
            break;
        }
        case 8: {

            //EDGE CASES NEED TO BE DELT WITH, IF RANK EXCEEDS BY A LITTLE AND STARTS WITH 0'S IT EXISTS 
            int sizeCutDown;
            printf("\nwhat size of cut down DB sequence?: ");
            scanf("%d",&sizeCutDown);
            n = 31 - __builtin_clz(sizeCutDown) + 1;
            int *neck = testGetClosestNeckInDBSeqPCR3(sizeCutDown,n);
            int *alpha = malloc(sizeof(int) * n);
            char buf[128];
            printf("input your string (0s and 1s only): ");
            scanf("%s", buf);
            for (int i = 0; i < n; i++) {
                alpha[i] = buf[i] - '0';
            }
            if ((1 << (n-1)) == sizeCutDown) {
                printf("Rank: %d\n", getRank(alpha,n));
                return;
            } else if ((1 << n) - 1 == sizeCutDown) {
                int temp = getRank(alpha,n);
                if (temp == (1<<n)){printf("String does not exist"); return;}
                printf("Rank: %d\n", getRank(alpha,n));
                return;
            } else if ((1 << n) - 2 == sizeCutDown){

                return;
            }


            //getting the size of the cut outs we need. 
            int rank = testRankDBseqPCR3(neck,n);
            int diff = rank-sizeCutDown;
            if (diff == 0){
                printf("Rank: %d\n", unCutRank);
                return;
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
                if (unCutRank > cutdownNecklacesRank[i]){
                    unCutRank = unCutRank - cuts[i];
                }
                else if (unCutRank > cutdownNecklacesRank[i]-cuts[i]){
                    printf("String does not exist");
                    return;
                }
            }
            if (unCutRank > sizeCutDown){
                printf("String does not exist %d\n", unCutRank);
                break;
            }
            printf("Rank: %d\n", unCutRank);

            printf("\n");
            break;
        }
        case 9: {
            
        }
    }
}