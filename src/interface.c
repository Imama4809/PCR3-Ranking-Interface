#include "../inc/interface.h"

void textInterface(){
    //options 
    // 1 rank PCR3 necklace
    // 2 rank PCR3 Lyndon Word
    // 3 unrank PCR3 necklace
    // 4 rank DB seq PCR3
    // 5 unrank DB seq PCR3
    int n, option;
    printf("what size of string (n value)?: ");
    scanf("%d",&n);
    // n=8;
    printf("pick an option\n");
    printf("1: rank PCR3 necklace\n");
    printf("2: rank PCR3 Lyndon Word\n");
    printf("3: unrank PCR3 necklace\n");
    printf("4: rank DB seq PCR3\n");
    printf("5: unrank DB seq PCR3\n");
    printf("option: ");
    scanf("%d",&option);
    switch (option){
        case 1: {
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
            int rank;
            printf("input your rank: ");
            scanf("%d",&rank);
            int *neck = testUnrankNecklacePCR3(rank,n);
            printf("string: ");
            for (int i=0;i<n;i++){
                printf("%d",neck[i]);
            }
            printf("\n");
            free(neck);
            break;
        }
        case 4: {
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
        }
    }
}