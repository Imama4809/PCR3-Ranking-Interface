#include <check.h>
#include <string.h>
#include "../inc/PCR3NeckAndLyndon.h"
#include "../inc/helper.h"


START_TEST(testingNewRankAlgorithm){
    int n = 12;
    int *alpha = malloc(sizeof(int)*n);
    for (int i =0;i<n;i++) alpha[i] = 2;
    for (int val = 0; val < (1 << n); val++) {
        int s[n];
        int sCopy[n];
        for (int i = 0; i < n; i++) {
            s[n - 1 - i] = (val >> i) & 1;
            sCopy[n - 1 - i] = (val >> i) & 1;
        }
        for (int i=0;i<n;i++) {s[i]++;sCopy[i]++;}
        int rankOld = PCR3Count(s,n);
        int rankNew = PCR3CountNew(sCopy,n);
        // use s here
        
        // if (pow(2,n)-rankOld != rankNew) {
        //     for(int i=0;i<n;i++) {printf("%d",s[i]);}
        //     printf(" %d %d %d\n",pow(2,n),rankOld,rankNew);
        // }
        ck_assert_int_eq(pow(2,n)- rankOld, rankNew);
    }       

    free(alpha);
}

// START_TEST(testingNewRankSequenceAlgorithm){

// }


Suite *PCR3_Necklace_Suite(void){
    Suite *s = suite_create("PCR3_Necklace_Suite");
    TCase *tc_core = tcase_create("Core_Tests");
    tcase_set_timeout(tc_core, 60);
    tcase_add_test(tc_core,testingNewRankAlgorithm);

    suite_add_tcase(s,tc_core);
    return s;
}