#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "connectfour.h"

/*
 * Connect Four main function
 */
int main(int argc, char** argv) {
  srand (time(NULL));
  board_type * b = createBoard(BOARD_DIM_X, BOARD_DIM_Y);

  int input;
  while((winnerIs(b)==0) && validMovesLeft(b))
  {
    if(cp(b) == PLAYER_ONE)	
    {
      scanf("%d", &input);
      makeMove(b,input);// Make it so!
    }
    else
    {
      makeMove(b, getReasonedMove(b));// Make it so!
    }
    printf("%s\n", toString(b));
  }
  return 0;
}


