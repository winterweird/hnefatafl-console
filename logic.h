#ifndef LOGIC_H
#define LOGIC_H

#include "board.h"

char tileEmpty(TILE);                  // Returns 1 if all the fields in the tile are zero
char posEqual(TILE, TILE);             // Returns 1 if the tiles' positions (t.x and t.y) are equal
char isInLine(TILE, TILE);             // Returns true if either the tiles' t.x are equal or the t.y are equal
char ownsPiece(char, TILE);            // Returns true if the player specified by char player owns the piece at the tile
char hasEnemy(int, TILE[], int);       // Returns true if there's an enemy in the specified direction of the tile at board[index]
char moveValidity(TILE, TILE, TILE[]); // Returns 0 if the move is a valid move, else an integer corresponding to an error code
void printErrorString(int);            // Print the string corresponding to the code returned by moveValidity
void makeMove(TILE, TILE, TILE[]);     // Move the piece at tile1 to tile2, removing any enemies captured in the process
char hasWinner(TILE[], TILE);          // Returns 0 if there is no winner, or 1 or 2 depending on who the winner was

#endif /* LOGIC_H */