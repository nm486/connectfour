// Connect Four Board implementation file
#include "board.h"

point_type* newPoint(int a, int b)
{
  point_type* p = (point_type*)malloc(sizeof(point_type));
  p->x=a;
  p->y=b;
  p->state=EMPTY;
  return p;
}

board_type* createBoard(int a, int b)
{
  board_type* p = (board_type*)malloc(sizeof(board_type));
  p->cols=a;
  p->rows=b;
  p->lm=-1;
  p->cp=PLAYER_ONE;
  p->heights = (int*)malloc(p->cols * sizeof(int));
  p->grid = (point_type***)malloc(p->cols * sizeof(point_type**));
  p->heightBits = (char*)malloc(BOARD_DIM_X * sizeof(char));
  int x, y;
  
  for(x = 0;x < p->cols;x++)
  {
    p->grid[x] =(point_type**)malloc(p->rows * sizeof(point_type*));
    p->heights[x] = 0;
    for(y = 0;y< p->rows;y++)
    {
      p->grid[x][y] = newPoint(x,y);
    }
    p->heightBits[x] = (char)(BOARD_DIM_Y1*x);
  }
  
  p->moves = (int*)malloc(p->cols * p->rows * sizeof(int));
  p->cl = generateCL(p->grid);
  p->bitboard = (bitBoard*)calloc(NUM_PLAYERS, sizeof(bitBoard));

  return p;
}

void deletePoint(point_type* p)
{
  free(p);
}

int equalsPosition(point_type* a, point_type* b)
{
  return a->x == b->x && a->y == b->y;
}

point_type*** generateCL(point_type*** grid)
{
  point_type*** lines = (point_type***)malloc(69 * sizeof(point_type**));
  int i, x, y, t;
  int count = 0;
  
  for(i = 0;i < 69; i++)
  {
    lines[i] = (point_type**)malloc(4 * sizeof(point_type*));
  }

  for(y = 0;y < 6;y++)
  {
    for(x = 0;x < 4;x++)
    {
      point_type** temp = (point_type**)malloc(4 * sizeof(point_type*));
      for(i = x;i < x + 4;i++)
      {
        temp[i-x]=grid[i][y];
      }
      lines[count]=temp;
      count++;
    }
  }

  for(x = 0;x < 7;x++)
  {
    for(y = 0;y < 3;y++)
    {
      point_type** temp = (point_type**)malloc(4 * sizeof(point_type*));
      for( i=y;i<y+4;i++)
      temp[i-y]=grid[x][i];
      lines[count]=temp;
      count++;
    }
  }

  for(x = 0;x < 4;x++)
  {
    for(y = 0;y < 3;y++)
    {
      point_type** temp = (point_type**)malloc(4 * sizeof(point_type*));
      for( t=x,i=y;t<x+4 && i<y+4;t++,i++)
        temp[i-y]=grid[t][i];
      lines[count]=temp;
      count++;
    }
  }
  
  for(x = 0;x < 4;x++)
  {
    for(y = 5;y > 2;y--)
    {
      point_type** temp = (point_type **)malloc(4 * sizeof(point_type*));
      for(t = x,i = y;t < x + 4 && i > -1;t++,i--)
        temp[t-x]=grid[t][i];
      lines[count]=temp;
      count++;
    }
  }
  return lines;
}

void updateBitboard(board_type* p, int col)
{
  p->bitboard[p->lm & 1] ^= (bitBoard)1<<p->heightBits[col]++;  
}

void deleteBoard(board_type* p)
{
  free(p->cl);
  free(p->grid);
  free(p->heights);
  free(p->moves);
  free(p->heightBits);
  free(p);
}

int cp(board_type* b)
{
  return b->cp;
}

int validMovesLeft(board_type* b)
{
  return b->lm < ((b->cols * b->rows) - 1);
}
