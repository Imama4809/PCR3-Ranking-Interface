#include <check.h>
#include <string.h>
#include "../inc/helper.h"

#define N 8

START_TEST(test_smallestPCR3StrictlyAbove_all_8bit_strings) {
    int alpha[N];
    for (int i = 0; i < N; i++) {
        alpha[N - 1 - i] = (_i >> i) & 1;
    }

    int start = 0;
    for (int i = 0; i < N; i++) start = (start << 1) | alpha[i];

    int expected[N];
    int expectedStatus = -1;
    for (int val = start + 1; val < (1 << N); val++) {
        for (int i = 0; i < N; i++) {
            expected[N - 1 - i] = (val >> i) & 1;
        }
        if (isNecklacePCR3(expected, N)) {
            expectedStatus = 1;
            break;
        }
    }

    int actual[N];
    memcpy(actual, alpha, sizeof(alpha));
    int actualStatus = smallestPCR3StrictlyAbove(actual, N);

    // ck_assert_int_eq(actualStatus, expectedStatus);

    if (expectedStatus == 1) {
        // for (int i =0;i<N;i++){
        //     printf("%d",alpha[i]);
        // }
        // printf(" ");
        // for (int i =0;i<N;i++){
        //     printf("%d",expected[i]);
        // }
        // printf(" ");
        // for (int i =0;i<N;i++){
        //     printf("%d",actual[i]);
        // }
        // printf("\n");
        ck_assert_msg(areArraysEqual(actual, expected, N),
                      "Mismatch for input %d: got wrong necklace", _i);
    }
}
END_TEST


START_TEST(test_greatestPCR3Below_all_8bit_strings) {
    int alpha[N];
    for (int i = 0; i < N; i++) {
        alpha[N - 1 - i] = (_i >> i) & 1;
    }
 
    int start = 0;
    for (int i = 0; i < N; i++) start = (start << 1) | alpha[i];
 
    int expected[N];
    for (int val = start - 1; val >= 0; val--) {
        for (int i = 0; i < N; i++) {
            expected[N - 1 - i] = (val >> i) & 1;
        }
        if (isNecklacePCR3(expected, N)) {
            break;
        }
    }
 
    int actual[N];
    memcpy(actual, alpha, sizeof(alpha));
    greatestPCR3Below(actual, N);

    for (int i =0;i<N;i++){
        printf("%d",alpha[i]);
    }
    printf(" ");
    for (int i =0;i<N;i++){
        printf("%d",expected[i]);
    }
    printf(" ");
    for (int i =0;i<N;i++){
        printf("%d",actual[i]);
    }
    printf("\n");
    
    ck_assert_msg(areArraysEqual(actual, expected, N),
                  "Mismatch for input %d: got wrong necklace", _i);
}END_TEST

Suite *PCR3_Helper_Suite(void) {
    Suite *s = suite_create("PCR3_Helper_Suite");
    TCase *tc_core = tcase_create("Core");

    tcase_add_loop_test(tc_core, test_smallestPCR3StrictlyAbove_all_8bit_strings, 0, 1 << N);
    tcase_add_loop_test(tc_core, test_greatestPCR3Below_all_8bit_strings, 1, 1 << N);
    suite_add_tcase(s, tc_core);

    return s;
}