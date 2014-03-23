// Connect Four Header File
#include <stdlib.h>
#include <limits.h>

#define BOARD_DIM_X 7
#define BOARD_DIM_Y 6
#define SCORE_MODIFIER 16

static const int PLAYER_ONE = 1;
static const int PLAYER_TWO = -1;
static const int EMPTY = 0;

typedef struct point point_type;
struct point
{
  int x, y, state;
};

typedef struct board board_type;
struct board {

  point_type*** grid;
  int* heights;

  int cols;
  int rows;

  int* moves;
  int lm;  // moves made / remaining?  possible bug with -1

  int cp;
  point_type*** cl;
};

point_type* newPoint(int a, int b);

void deletePoint(point_type* p);

int equalsPosition(point_type* a, point_type* b);

void setState(point_type* a, int player);

int getState(point_type* a);

point_type*** generateCL(point_type *** grid);

board_type * createBoard(int a, int b);

void deleteboard(board_type* p);

int validMove(board_type * b, int column);

void makeMove(board_type * b, int column);

void undoMove(board_type * b);

int validMovesLeft(board_type * b);

int getScore(point_type * points[]);

int getStrength(board_type * b);

int winnerIs(board_type * b);

char * toString(board_type * b);

int cp(board_type * b);

int getRandomPlayerMove(board_type *b);

int minValue(board_type * cB, int ply);

int maxValue(board_type * cB, int ply);

int getReasonedMove(board_type * cB);