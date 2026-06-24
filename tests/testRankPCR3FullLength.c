#include <check.h>
#include "trials.h"



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
    int alpha[10] = {1,0,1,0,0,0,1,1,1};
    int n = 9;
    int rank = testRankDBseqPCR3(alpha,n);
    ck_assert_int_eq(rank,454);

    int beta[10] = {0};
    for (int i =n-1;i>=0;i--){
        beta[i] = 1;
        rank = testRankDBseqPCR3(beta,n);
        if (i ==0 ){ ck_assert_int_eq(rank,512); break;}
        ck_assert_int_eq(rank,i);
    }

}

// Create and return the suite for string functions
Suite *PCR3_Full_Suite(void) {
    Suite *s = suite_create("PCR3_Full_Suite");
    TCase *tc_core = tcase_create("Core_Tests");

    tcase_add_test(tc_core,test_necklace_rank);
    tcase_add_test(tc_core,test_lyndon_rank);
    tcase_add_test(tc_core,test_rank_in_seq);
    suite_add_tcase(s, tc_core);

    return s;
}
