#include <check.h>
#include <stdlib.h>

// Forward declare the suite creation functions from other files
Suite *PCR3_Full_Suite(void);
Suite *PCR3_Cut_Suite(void);
Suite *PCR3_Helper_Suite(void);
Suite *PCR3_Necklace_Suite(void);
Suite *PCR3_Step_Suite(void);


int main(void) {
    int number_failed;
    SRunner *sr = srunner_create(PCR3_Cut_Suite()); // Initialize with first suite
    
    // Add additional suites here
    // srunner_add_suite(sr, PCR3_Necklace_Suite());
    // srunner_add_suite(sr, PCR3_Cut_Suite());
    // srunner_add_suite(sr, PCR3_Step_Suite());
    // srunner_add_suite(sr, PCR3_Helper_Suite());

    // Run all suites
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}