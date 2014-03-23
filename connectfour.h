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

  point_type*** grid; // two-dimensional array of pointers of type point_type
  int* heights; // an array of size cols representing the current stack height for each column

  int cols;  // number of columns in board
  int rows;  // number of rows in board

  int* moves;
  int lm;  // moves made / remaining?  possible bug with -1

  int cp; // current player of board
  point_type*** cl;
};

point_type* newPoint(int a, int b);

void deletePoint(point_type* p);

int equalsPosition(point_type* a, point_type* b);

void setState(point_type* a, int player);

int getState(point_type* a);

point_type*** generateCL(point_type *** grid);

// Creates a new empty Connect Four board with dimensions AxB.
board_type* createBoard(int a, int b);

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