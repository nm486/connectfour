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
  while((winnerIs(b) == 0) && validMovesLeft(b))
  {
    if(cp(b) == PLAYER_ONE)	
    {
      valid = 0;
      printf("Your turn!\nPlease enter a number from 0 to %d to play a piece into a column (numbered 0 to %d from left to right.)\n", BOARD_DIM_X-1, BOARD_DIM_X-1);
      do 
      {
        scanf("%d", &input);
        if (b->heights[input] == BOARD_DIM_Y)
        {
          printf("Column %d is full! Please input another column.\n");
        }
        else if (input < 0 || input > BOARD_DIM_X-1)
        {
          printf("You must input a number between 0 and %d.\n", BOARD_DIM_X-1);
        }
        else
        {
          valid = 1;
        }
      } while (valid == 0);
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
    updateBitboard(b, input);
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



