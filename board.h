#ifndef BOARD_H
#define BOARD_H

typedef struct tile {
    unsigned char piece : 2; // none, s1, s2, king
    unsigned char attr  : 2; // none, exit, home
    unsigned char x     : 4;
    unsigned char y     : 4;
} TILE;

// Note: I could've used a 2D array for the game board, but I decided to use
// a 1D array because of less loop nesting

void initBoard(TILE[]);                  // Initializes an 11x11 board according to the 11x11 setup of hnefatafl
int getIndex(TILE);                      // Based on the x and y fields of tile, return the index of the tile in the board-array
int xsp(int);                            // Returns the X value of the screen coordinate corresponding to the given tile.x-value
int ysp(int);                            // Returns the Y value of the screen coordinate corresponding to the given tile.y-value
void printBoard(TILE[]);                 // Print the board according to the given character representations
void printIntense(TILE);                 // Print a tile's character representation in intense white
TILE selectTile(TILE[], TILE);           // Navigate the board using WASD or arrow keys, return the chosen tile at space/return
TILE getRelativeTile(int, TILE, TILE[]); // Return the tile to the LEFT, RIGHT, UP or DOWN relative to the given tile

#endif /* BOARD_H */