// Connect Four Source File
#include <stdio.h>
#include "connectfour.h"

static void setState(point_type* a, int player)
{
  a->state=player;
}

static int getState(point_type* a)
{
  return a->state;
}

static int validMove(board_type* b, int column)
{
  return b->heights[column]<b->rows;
}

void makeMove(board_type* b, int column)
{
  setState(b->grid[column][b->heights[column]],b->cp); // set the point to be owned by player

  b->heights[column]++;
  b->lm++;
  b->moves[b->lm]=column;
  b->cp=-(b->cp);
}


void undoMove(board_type* b)
{
  int move = b->moves[b->lm];
  setState(b->grid[move][b->heights[move]-1],(EMPTY));
  b->heights[move]--;
  b->lm--;
  b->cp=-(b->cp);
}

int getScore(point_type* points[]) 
{
  int playerone = 0, playertwo = 0;
  int i, state;
  
  for(i = 0;i < 4;i++)
  {
    state = getState(points[i]);
    if(state == PLAYER_ONE)
    {
      playerone++;
    }
    else if(state == PLAYER_TWO)
    {
      playertwo--;
    }
  }
  
  if(!(playerone > 0 && playertwo < 0))
  {
    return (playerone != 0)? playerone:playertwo;
  }
  else
  {
    return 0;
  }
}

int getStrength(board_type * b)
{
  int sum = 0;
  int weights[] = {0,1,10,50,600};
  int i, score;
  
  for(i = 0;i < 69;i++)
  {
    score = getScore(b->cl[i]);
    sum+=(score > 0) ? weights[abs(score)] : -weights[abs(score)]; //fixed redundant calls, short line
  }
  return sum + (b->cp==PLAYER_ONE? SCORE_MODIFIER : -SCORE_MODIFIER);
}

int winnerIs(board_type* b)
{
  bitBoard playersB[NUM_PLAYERS] = {b->bitboard[0], b->bitboard[1]};
  bitBoard horizontalB[NUM_PLAYERS], verticalB[NUM_PLAYERS], diagB1[NUM_PLAYERS], diagB2[NUM_PLAYERS];
  int i, player = PLAYER_ONE;
  
  for (i = 0;i < NUM_PLAYERS;i++)
  {
    diagB1[i] = playersB[i] & (playersB[i] >> BOARD_DIM_Y);
    if (diagB1[i] & (diagB1[i] >> 2*BOARD_DIM_Y))
    {
      return player;
    } 
    horizontalB[i] = playersB[i] & (playersB[i] >> BOARD_DIM_Y + 1);
    if (horizontalB[i] & (horizontalB[i] >> 2*BOARD_DIM_Y1))
    {
      return player;
    }
    diagB2[i] = playersB[i] & (playersB[i] >> BOARD_DIM_Y2);
    if (diagB2[i] & (diagB2[i] >> 2*BOARD_DIM_Y2))
    {
      return player;
    }
    verticalB[i] = playersB[i] & (playersB[i] & (playersB[i] >> 1));
    if (verticalB[i] & (verticalB[i] >> 2))
    {
      return player;
    }
    player = PLAYER_TWO;
  }
  return 0;
}

int getRandomPlayerMove(board_type* b)
{
  int val =-1;
  int possible[BOARD_DIM_X];
  int i;
  
  for(i = 0; i < BOARD_DIM_X; i++)
  {
    if(validMove(b,i))
    {
      possible[i] = 1;
    }
    else
    {
      possible[i] = 0;
    }
  }

  while(val == -1)
  {
    int rad = rand() % BOARD_DIM_X;
    if(possible[rad] == 1)
    {
      val = rad;
    }
  }
  return val;
}
 
// should return a number
int getReasonedMove(board_type* cB)
{
  int moves[BOARD_DIM_X];
  int highest = 0;
  int i;
  for(i = 0;i < BOARD_DIM_X; i++)
  {
    moves[i] = INT_MIN;
    if(validMove(cB, i))
    {
      makeMove(cB,i);
      moves[i] = minValue(cB,4);
      if(moves[i]>=moves[highest])
      {
        highest=i;
      }
      undoMove(cB);
    } 
  }
  return highest;
}

// don't change this unless you understand it
int minValue(board_type* cB, int ply)
{
  int moves[BOARD_DIM_X];
  int lowest = 0;
  int i;
  for(i = 0; i < BOARD_DIM_X; i++)
  {
    moves[i] = INT_MAX;
    if(validMove(cB,i))
    {
      makeMove(cB,i);
      if((winnerIs(cB) == 0) && ply > 0)
      {
        moves[i] = maxValue(cB,ply-1);
      }
      else 
      {
        moves[i] = -getStrength(cB);
      }
      if(moves[i] < moves[lowest])
      {
        lowest=i;
      }
      undoMove(cB);
    }
  }
  return moves[lowest];
}

//careful with this
int maxValue(board_type* cB, int ply)
{
  int moves[BOARD_DIM_X];
  int highest = 0;
  int i;
  
  for(i = 0; i < BOARD_DIM_X; i++)
  {
    moves[i] = INT_MAX;
    if(validMove(cB,i))
    {
      makeMove(cB,i);
      if((winnerIs(cB) == 0) && ply>0)
      {
        moves[i] = minValue(cB,ply-1);
      }
      else 
      {
        moves[i] =-getStrength(cB);
      }
      if(moves[i]<moves[highest])
      {
        highest=i;
      }
      undoMove(cB);
    }
  }
  return moves[highest];
}

char* toString(board_type* b)
{
  char* temp = (char*)malloc(b->rows*(b->cols+1)*sizeof(char)+1);
  char* curr = temp;
  int x, y, state;

  for(y = b->rows-1;y > -1;y--)
  {
    for(x = 0;x < b->cols;x++)
    {
      state = getState(b->grid[x][y]);
      if(state==EMPTY)
      {
        *curr = '-';
      }
      else if(state==PLAYER_ONE)
      {
        *curr = 'O';
      }
      else
      {
        *curr = 'X';
      }
      curr++;
    }
    *curr = '\n';
    curr++;
  }
  return temp;
}

int isInputValid(board_type* b, int input, int valid)
{
  if (valid != TEST_FLAG)
  {
    if (valid != 1 || (getchar() != '\n'))
    {
      while (getchar() != '\n');
      printf("You must input a number between 0 and %d.\n", BOARD_DIM_X-1);
      return 0;
    }
    if (isalpha(input)) // check if input is an actual number
    {
      printf("You must input a number between 0 and %d.\n", BOARD_DIM_X-1);
      return 0;
    }
    if (b->heights[input] == BOARD_DIM_Y)
    {
      printf("Column %d is full! Please input another column.\n");
      return 0;
    }
    else if (input < 0 || input > BOARD_DIM_X-1)
    {
      printf("You must input a number between 0 and %d.\n", BOARD_DIM_X-1);
      return 0;
    }
  }
  else // suppress output for unit testing
  {
    if (valid != 1 || (getchar() != '\n'))
    {
      while (getchar() != '\n');
      return 0;
    }
    if (isalpha(input)) // check if input is an actual number
    {
      return 0;
    }
    if (b->heights[input] == BOARD_DIM_Y)
    {
      return 0;
    }
    else if (input < 0 || input > BOARD_DIM_X-1)
    {
      return 0;
    }
  }
  return 1;
}