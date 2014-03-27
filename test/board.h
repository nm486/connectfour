// Connect Four Board Header file
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "options.h"

typedef uint64_t bitBoard;

// Defines a single Connect Four board point.
typedef struct point point_type;
struct point
{
  int x, y, state; // state indicates the player who has placed a piece in this point, zero otherwise
};

// Defines the Connect Four board.
typedef struct board board_type;
struct board {

  point_type*** grid; // two-dimensional array of pointers of type point_type
  int* heights; // an array of size cols representing the current stack height for each column

  int cols;  // number of columns in board
  int rows;  // number of rows in board

  int* moves; // stores an ordered list of previous moves (column number)
  int lm;  // moves made / remaining

  int cp; // current player of board
  point_type*** cl; // an array containing all the 69 winning conditions of a 7x6 Connect Four board.  Used in the old implementation
  
  bitBoard* bitboard; // NEW: efficient 64-bit integer to perform winning condition checking. 0th element is player one's board, 1st element is player two's board 
  char* heightBits; // holds bit index of lowest free square in each column
};

// Create a new point object
point_type* newPoint(int a, int b);

// Delete a point object
void deletePoint(point_type* p);

// Returns whether or not the two points are in the same board location
int equalsPosition(point_type* a, point_type* b);

// Generates a 2d array of all 69 winning conditions
// We keep this because the AI engine requires this.
point_type*** generateCL(point_type*** grid);

// Updates the appropriate bitboard after a final move has been made.
void updateBitboard(board_type* p, int col);

// Creates a new empty Connect Four board with dimensions AxB.
board_type* createBoard(int a, int b);

// Deletes a game board.
void deleteBoard(board_type* p);

// Returns the current player
int cp(board_type* b);

// Returns whether or not if any points are still unoccupied
int validMovesLeft(board_type* b);