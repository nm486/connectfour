// Connect Four Source File
#include "connectfour.h"

point_type* newPoint(int a, int b)
{
  point_type* p = (point_type*)malloc(sizeof(point_type));
  p->x=a;
  p->y=b;
  p->state=EMPTY;
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

static void setState(point_type* a, int player)
{
  a->state=player;
}

static int getState(point_type* a)
{
  return a->state;
}

point_type*** generateCL(point_type*** grid)
{
  point_type*** lines = (point_type ***)malloc(69 * sizeof(point_type **));
  int i, x, y, t;
  int count = 0;
  
  for(i = 0; i < 69; i++)
  {
    lines[i] = (point_type**)malloc(4 * sizeof(point_type*));
  }

  for(y = 0; y < 6; y++)
  {
    for(x = 0; x < 4; x++)
    {
      point_type** temp = (point_type**)malloc(4 * sizeof(point_type*));
      for(i=x;i<x+4;i++)
      {
        temp[i-x]=grid[i][y];
      }
      lines[count]=temp;
      count++;
    }
  }

  for( x=0;x<7;x++)
  {
    for( y=0;y<3;y++)
    {
      point_type** temp = (point_type**)malloc(4 * sizeof(point_type*));
      for( i=y;i<y+4;i++)
      temp[i-y]=grid[x][i];
      lines[count]=temp;
      count++;
    }
  }

  for( x=0;x<4;x++)
  {
    for( y=0;y<3;y++)
    {
      point_type** temp = (point_type**)malloc(4 * sizeof(point_type*));
      for( t=x,i=y;t<x+4 && i<y+4;t++,i++)
        temp[i-y]=grid[t][i];
      lines[count]=temp;
      count++;
    }
  }
  
  for(x=0;x<4;x++)
  {
    for(y=5;y>2;y--)
    {
      point_type** temp = (point_type**)malloc(4 * sizeof(point_type*));
      for(t=x,i=y;t<x+4 && i>-1;t++,i--)
        temp[t-x]=grid[t][i];
      lines[count]=temp;
      count++;
    }
  }
  return lines;
}

board_type* createBoard(int a, int b)
{
  board_type * p = (board_type*)malloc(sizeof(board_type));
  p->cols=a;
  p->rows=b;
  p->lm=-1;
  p->cp=PLAYER_ONE;
  p->heights = (int *)malloc(p->cols * sizeof(int));
  p->grid = (point_type ***)malloc(p->cols * sizeof(point_type **));
  
  int x, y;
  
  for(x = 0; x < p->cols; x++)
  {
    p->grid[x] =(point_type **)malloc(p->rows * sizeof(point_type *));
    p->heights[x] = 0;
    for(y = 0; y< p->rows; y++)
    {
      p->grid[x][y] = newPoint(x,y);
    }
  }
  
  p->moves = (int *)malloc(p->cols * p->rows * sizeof(int));
  p->cl = generateCL(p->grid);
  
  return p;
}

void deleteBoard(board_type* p)
{
  free(p->cl);
  free(p->grid);
  free(p->heights);
  free(p->moves);
  free(p);
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
  b->cp=-b->cp;
}


void undoMove(board_type* b)
{
  setState(b->grid[b->moves[b->lm]][b->heights[b->moves[b->lm]]-1],(EMPTY));
  b->heights[b->moves[b->lm]]--;
  b->lm--;
  b->cp=-b->cp;
}


int validMovesLeft(board_type* b)
{
  return b->lm<((b->cols*b->rows)-1);
}

int getScore(point_type * points[]) 
{
  int playerone=0;
  int playertwo=0;
  int i, state;
  for( i=0;i<4;i++)
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
  
  if(!(playerone>0 && playertwo<0))
  {
    return (playerone!=0)?playerone:playertwo;
  }
  else
  {
    return 0;
  }
}

int getStrength(board_type* b)
{
  int sum=0;
  int weights[] = {0,1,10,50,600};
  int i, score;
  
  for(i=0;i<69;i++)
  {
    score = getScore(b->cl[i]);
    sum+=(score > 0) ? weights[abs(score)] : -weights[abs(score)]; //fixed redundant calls, short line
  }
  return sum + (b->cp==PLAYER_ONE? SCORE_MODIFIER : -SCORE_MODIFIER);
}

int winnerIs(board_type* b)
{
  int i, score;
  for(i=0;i<69;i++)
  {
    score = getScore(b->cl[i]);
    if(score == 4 )
    {
      return PLAYER_ONE;
    }
    else if(score == -4)
    {
      return PLAYER_TWO;
    }
  }
  return 0;
}

char* toString(board_type* b)
{
  char * temp = (char *)malloc(b->rows*(b->cols+1)*sizeof(char)+1);
  char * curr = temp;
  int x, y, state;

  for( y=b->rows-1;y>-1;y--)
  {
    for( x=0;x<b->cols;x++)
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

int cp(board_type * b)
{
  return b->cp;
}

int getRandomPlayerMove(board_type* b)
{
  int val =-1;
  int possible[7];
  int i;
  
  for( i = 0; i <7; i++)
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
    int rad = rand() % 7;
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
  int moves[7];
  int highest = 0;
  int i;
  for( i=0;i<7;i++)
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
  int moves[7];
  int lowest = 0;
  int i;
  for( i=0;i<7;i++)
  {
    moves[i] = INT_MAX;
    if(validMove(cB,i))
    {
      makeMove(cB,i);
      if((winnerIs(cB) == 0) && ply>0)
      {
        moves[i] = maxValue(cB,ply-1);
      }
      else 
      {
        moves[i] = -getStrength(cB);
      }
      if(moves[i]<moves[lowest])
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
  int moves[7];
  int highest = 0;
  int i;
  
  for( i=0;i<7;i++)
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

int isInputValid(board_type* b, int input, int valid)
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
  return 1;
}