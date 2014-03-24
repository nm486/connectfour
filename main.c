#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>

#include "connectfour.h"

double getTime()
{
  struct timeval tv;
  struct timezone tz;
  int i;

  i = gettimeofday(&tv,&tz);
  return ( (double) tv.tv_sec + (double) tv.tv_usec * 1.e-6 );
}

/*
 * Connect Four main function
 */
int main(int argc, char** argv) {
  srand (time(NULL));
  board_type * b = createBoard(BOARD_DIM_X, BOARD_DIM_Y);
  double start, stop;
  int input, valid = 0;
  
  printf("Welcome to Connect Four!\n");
  printf("The objective of the game is to connect four of your pieces in a row,\neither horizontally, vertically, or diagonally, before the computer does.\n\n");
  while((winnerIs(b) == 0) && validMovesLeft(b))
  {
    if(cp(b) == PLAYER_ONE)	
    {
      valid = 0;
      printf("It's Your turn!\nPlease enter a number from 0 to %d to play a piece into a column\n(numbered 0 to %d from left to right.)\n", BOARD_DIM_X-1, BOARD_DIM_X-1);
      do 
      {
        valid = scanf("%d", &input);
      } while (isInputValid(b, input, valid) == 0);
      makeMove(b,input);// Make it so!
    }
    else
    {
      printf("Computer making its move...\n");
      start = getTime();
      input = getReasonedMove(b);
      makeMove(b, input);// Make it so!
      stop = getTime();
      printf("Time for AI to make move: %f seconds.\n", stop-start);
    }
    printf("%s\n", toString(b));
  }
  
  if (winnerIs(b) == -1)
  {
    printf("Congratulations! You have won!\n");
  }
  else
  {
    printf("The computer has won!\n");
  }
  return 0;
}



