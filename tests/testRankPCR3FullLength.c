#include <check.h>
#include "../inc/trials.h"



START_TEST(test_necklace_rank){
    int alpha[7] = {1,0,1,1,0,0};
    int n = 6;
    int rank = testRankNecklacePCR3(alpha,n);
    ck_assert_int_eq(rank,6);
}

START_TEST(test_lyndon_rank){
    int alpha[7] = {1,1,0,0,0,0};
    int n = 6;
    int rank = testRankLyndonWordPCR3(alpha,n);
    ck_assert_int_eq(rank,6);
}
START_TEST(test_rank_in_seq){
    //this checks the wraparound for n=9;
    int alpha[10] = {1,0,1,0,0,0,1,1,1};
    int n = 9;
    int rank = testRankDBseqPCR3(alpha,n);
    ck_assert_int_eq(rank,58);

    int beta[10] = {0};
    for (int i =n-1;i>=0;i--){
        beta[i] = 1;
        rank = testRankDBseqPCR3(beta,n);
        if (i ==0 ){ ck_assert_int_eq(rank,512); break;}
        ck_assert_int_eq(rank,pow(2,n)-i);
    }
}

START_TEST(testRankAlgorithm){
    int n = 10;
    int *alpha = malloc(sizeof(int)*n);
    for (int i =0;i<n;i++) alpha[i] = 1;
    alpha[n-1] = 0;
    int dbLen;
    int *string = NULL;
    dbLen = DB(alpha,n,&string);
    int r = 1;
    for (int i =0;i<n;i++) alpha[i] = string[i];
    int rCheck = getRank(alpha,n);
    // ck_assert_int_eq(rCheck,r);
    // for (int i =0;i<dbLen;i++) printf("%d",string[i]);
    // printf("\n");
    for (int i =0;i<dbLen-n;i++){
        for (int i =0;i<n-1;i++) alpha[i] = alpha[i+1];
        alpha[n-1] = string[i+n];
        // for (int j = 0;j<n;j++)printf("%d",alpha[j]);
        // printf("\n");
        // printf("%d %d\n",r,rCheck);
        rCheck = getRank(alpha,n)+1;
        r++;
        // for (int j =0;j<n;j++) printf("%d",alpha[j]);
        // printf(" %d %d\n",rCheck,r);
        ck_assert_int_eq(rCheck,r);
    }
}

START_TEST(testUnrankAlgorithm){
    int n = 10;
    int *alpha = malloc(sizeof(int)*n);
    int *unrankedStr = malloc(sizeof(int)*n);
    for (int i =0;i<n;i++) alpha[i] = 1;
    alpha[n-1] = 0;
    int dbLen;
    int *string = NULL;
    int tempR;
    dbLen = DB(alpha,n,&string);
    for (int i =0;i<n;i++) alpha[i] = string[i];
    // printf("\n");
    for (int i =1;i<dbLen;i++){
        unrank(i,n,unrankedStr);
        // for (int i=0;i<n;i++) printf("%d",unrankedStr[i]);
        // printf("\n");
        tempR = getRank(unrankedStr,n);
        // printf("Actual rank:%d\n", i);
        // printf("Formula rank: %d\n",tempR);
        ck_assert_int_eq(tempR,i);
    }
}

// Create and return the suite for string functions
Suite *PCR3_Full_Suite(void) {
    Suite *s = suite_create("PCR3_Full_Suite");
    TCase *tc_core = tcase_create("Core_Tests");
    tcase_set_timeout(tc_core, 60);

    tcase_add_test(tc_core,test_necklace_rank);
    tcase_add_test(tc_core,test_lyndon_rank);
    tcase_add_test(tc_core,test_rank_in_seq);
    tcase_add_test(tc_core,testRankAlgorithm);
    tcase_add_test(tc_core,testUnrankAlgorithm);
    suite_add_tcase(s, tc_core);

    return s;
}

