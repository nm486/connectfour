#ifndef TESTS_H
#define TESTS_H

#define INPUTFILE "test_input.io"

/* Arbitrary floating point tolerance, TODO decide correct value */
#define TEST_FLOAT_TOL 0.0001
#define TEST_DOUBLE_TOL 0.00000001

#endif

void test_Landscape_file_init();
void test_Landscape_empty_init();
void test_Landscape_random_init();
void test_Landscape_dstr();
void test_SimVars_init();
void test_SimVars_user_init();
void test_SimVars_default_init();
void test_get_population_new();
void test_simulation();
void test_get_user_input();
void test_output_to_ppm();
void test_LandSquare_init();
void test_LandArea_init();
void test_num_input_check();
void test_file_name_check();
