#include <check.h>


// Create and return the suite for string functions
Suite *PCR3_Step_Suite(void) {
    Suite *s = suite_create("PCR3_Step_Suite");
    TCase *tc_core = tcase_create("Core_Tests");
    tcase_set_timeout(tc_core, 60);

    suite_add_tcase(s, tc_core);

    return s;
}

