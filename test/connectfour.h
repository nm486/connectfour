// Connect Four Header File
// Contains functions that are more gameflow-specific
#include <stdlib.h>
#include <limits.h>
#include "board.h"

// Sets the "owner" of specified point to specified player
static inline void setState(point_type* a, int player) __attribute__((always_inline));

// Returns the "owner" of the specified point
static inline int getState(point_type* a) __attribute__((always_inline));

// Checks if a move is valid
static inline int validMove(board_type * b, int column) __attribute__((always_inline));

// Makes a move in the specified column on the board
void makeMove(board_type * b, int column);

// Undos the previous move
void undoMove(board_type * b);

// For a given winning scenario, return which player satisfies it, return 0 otherwise
int getScore(point_type * points[]);

// Used by the AI to determine what move to make next
int getStrength(board_type * b);

// New bitboard implementation.  Much faster!
// Based heavily off the bitboard implementation used in the fhourstones benchmark
// https://github.com/qu1j0t3/fhourstones/blob/master/Game.c
// Returns if a player has won the game, 0 otherwise.  
int winnerIs(board_type * b);

// Used by the AI.
int getRandomPlayerMove(board_type *b);

// Used by the AI.
int minValue(board_type * cB, int ply);

// Used by the AI.
int maxValue(board_type * cB, int ply);

// Used by the AI.
int getReasonedMove(board_type * cB);

// Outputs the current state of the game board
char * toString(board_type * b);