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
            int *neck = malloc(sizeof(int)*n);
            int *string = NULL;
            int stringLen;
            for (int i =0;i<n-1;i++) neck[i] = 1;
            neck[n-1]=0;
            stringLen = DB(neck,n, &string);
            // for (int i =0;i<n;i++) printf("0");
            printString(string,stringLen);
            printf("\n");
            free(neck);
            break;
        }
        case 7:{
            int sizeCutDown;
            printf("\nwhat size of cut down DB sequence?: ");
            scanf("%d",&sizeCutDown);
            n = 31 - __builtin_clz(sizeCutDown)+1;
            int *neck = testGetClosestNeckInDBSeqPCR3(sizeCutDown,n);
            int *string = NULL;
            int stringLen; 


            if ((1 << n) == sizeCutDown) {
                for (int i=0;i<n;i++) neck[i]=1;
                printf("%d",1);
                neck[n-1] = 0;
                stringLen = DB(neck,n,&string);
                printString(string,stringLen);
                printf("\n");
                return;
            } else if ((1 << n) - 1 == sizeCutDown) {
                for (int i=0;i<n;i++) neck[i]=1;
                // printf("%d",1);
                neck[n-1] = 0;
                stringLen = DB(neck,n,&string);
                printString(string,stringLen);
                printf("\n");
                return;
            } else if ((1 << n) - 2 == sizeCutDown){
                for (int i=0;i<n;i++) neck[i]=1;
                printf("1");
                neck[n-1] = 0;
                stringLen = cutDownDB(neck,(1<<n)-3,n,&string);
                printString(string,stringLen);
                printf("\n");
                return;
            }
            
            stringLen = cutDownDB(neck,sizeCutDown,n,&string);
            printf("\n");
            printString(string,stringLen);
            // printf("%d",stringLen);
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
                printf("HERE");
                printf("Rank: %d\n", getRank(alpha,n-1));
                return;
            } else if ((1 << (n-1)) - 1 == sizeCutDown) {
                int temp = getRank(alpha,n-1);
                if (temp == (1<<(n-1))){printf("String does not exist"); return;}
                printf("Rank: %d\n", temp);
                return;
            } else if ((1 << (n-1)) - 2 == sizeCutDown){
                printf("Note that this is the cut down de Bruijn sequence that cuts out the necklaces of all 1's and all 0's.\n");
                int temp = getRank(alpha,n-1);
                if (temp == (1<<(n-1)) || temp == (n-1)){printf("String does not exist"); return;}
                if (temp > (n-1)) temp--;
                printf("Rank: %d\n", temp);
                //NEED TO FIX THIS EDGE CASE
                return;
            }


            //getting the size of the cut outs we need. 
            int rank = rankCutDownDB(neck,alpha,sizeCutDown,n);
            printf("rank: %d",rank);
            break;
        }
        case 9: {
            int alpha[n];
            int sizeCutDown;
            printf("\nwhat size of cut down DB sequence?: ");
            scanf("%d",&sizeCutDown);
            n = 31 - __builtin_clz(sizeCutDown) + 1;
            int *neck = testGetClosestNeckInDBSeqPCR3(sizeCutDown,n);
            int position;
            printf("input the position you wish to unrank: ");
            scanf("%d", &position);

            if ((1 << (n-1)) == sizeCutDown) {
                unrank(position,n-1,alpha);
                printf("string: ");
                for (int i=0;i<n-1;i++) printf("%d",alpha[i]);
                return;
            } else if ((1 << (n-1)) - 1 == sizeCutDown) {
                if (position == (1<<(n-1))){position--;}
                unrank(position,n-1,alpha);
                printf("string: ");
                for (int i=0;i<n-1;i++) printf("%d",alpha[i]);
                return;
            } else if ((1 << (n-1)) - 2 == sizeCutDown){
                position++;
                if (position >= (1<<(n-1))){position = (1<<(n-1)) - 1;}
                unrank(position,n-1,alpha);
                printf("string: ");
                for (int i=0;i<n-1;i++) printf("%d",alpha[i]);
                return;
            }



            unrankCutDownDB(neck,position,sizeCutDown,n,alpha);
            printf("string: ");
            for (int i=0;i<n;i++) printf("%d",alpha[i]); 
            
        }
    }
}