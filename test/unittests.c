/*
 * Unit testing suite for Connect Four
 *
 */

#include <stdlib.h>
#include <stdio.h>

#include "connectfour.h"

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

void test_isInputValid() 
{
  int i, outOfBounds = 47, overflowRow = 0;
  board_type* b = createBoard(BOARD_DIM_X, BOARD_DIM_Y);
  CU_ASSERT_EQUAL(isInputValid(b, outOfBounds, TEST_FLAG), 0);
  for (i = 0; i < BOARD_DIM_Y; i++) 
  {
    makeMove(b, overflowRow);
  }
  CU_ASSERT_EQUAL(isInputValid(b, overflowRow, TEST_FLAG), 0);
  CU_ASSERT_EQUAL(isInputValid(b, 3, TEST_FLAG), 1);
  deleteBoard(b);
}

void test_updateBitboard() 
{
  board_type* b = createBoard(BOARD_DIM_X, BOARD_DIM_Y);
  makeMove(b, 0);
  updateBitboard(b, 0);
  makeMove(b, 1);
  updateBitboard(b, 1);
  CU_ASSERT_EQUAL(b->bitboard[0], (bitBoard)1); 
  CU_ASSERT_EQUAL(b->bitboard[1], (bitBoard)128); 
  deleteBoard(b);
}

void test_winnerIs() 
{
  int i;
  board_type* b = createBoard(BOARD_DIM_X, BOARD_DIM_Y);
  for (i = 0; i < 4; i++)
  {
    makeMove(b, 0);
    updateBitboard(b, 0);
    makeMove(b, i+1);
    updateBitboard(b, i+1);
  }
  CU_ASSERT_EQUAL(winnerIs(b), PLAYER_ONE); 
  CU_ASSERT_NOT_EQUAL(winnerIs(b), PLAYER_TWO); 
  deleteBoard(b);
}

/* Run test suite */
int main(int argc, char** argv) {
  /* Set up Suite */

  CU_pSuite testSuite = NULL;

  /* initialise CUnit test registry */
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  if(!(testSuite = CU_add_suite("Suite_1", NULL, NULL))) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* Here tests will be added */
  //TODO
  CU_add_test(testSuite, "isInputValid", test_isInputValid);
  CU_add_test(testSuite, "updateBitboard", test_updateBitboard);
  CU_add_test(testSuite, "winnerIs", test_winnerIs);

  /* Here <s>be dragons</s> we'll run the tests using Basic interface */
  //TODO
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();

  /* Exit returning CUNIT error val */
  return CU_get_error();
}
