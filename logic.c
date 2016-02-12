#include "logic.h"
#include "wnd.h"
#include <stdio.h>
#include <conio.h>

#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

#define UPKEYCODE 72
#define LEFTKEYCODE 75
#define RIGHTKEYCODE 77
#define DOWNKEYCODE 80

char tileEmpty(TILE t) {
    // should never be true for any actual tile
    return t.x == 0 && t.y == 0 && t.piece == 0 && t.attr == 0;
}
char posEqual(TILE t1, TILE t2) {
    return t1.x == t2.x && t1.y == t2.y;
}
char isInLine(TILE t1, TILE t2) {
    // return 1 if x is equal, -1 if y is equal, 0 otherwise
    return t1.x == t2.x ? 1 : t1.y == t2.y ? -1 : 0;
}
char ownsPiece(char player, TILE t) {
    return t.piece == player || player == 2 && t.piece == 3;
}
char hasEnemy(int dir, TILE board[], int index) {
    TILE t = board[index], l;
    switch (dir) {
        case LEFT:
            if (t.x == 0) return -1;
            l = board[t.y*11 + t.x-1];
            break;
        case RIGHT:
            if (t.x == 10) return -1;
            l = board[t.y*11 + t.x+1];
            break;
        case UP:
            if (t.y == 0) return -1;
            l = board[(t.y-1)*11 + t.x];
            break;
        case DOWN:
            if (t.y == 10) return -1;
            l = board[(t.y+1)*11 + t.x];
            break;
    }
    char player = t.piece - (t.piece==3);
    if (l.piece && !ownsPiece(player, l) || !l.piece && l.attr != 0) {
        return 1;
    }
    
    return 0;
}
char bordersKing(TILE tile, TILE kingTile) {
    if (tile.x == kingTile.x) {
        return tile.y == kingTile.y + 1 || tile.y == kingTile.y - 1;
    }
    else if (tile.y == kingTile.y) {
        return tile.x == kingTile.x + 1 || tile.x == kingTile.x -1;
    }
    return 0;
}
char moveValidity(TILE t1, TILE t2, TILE board[]) {
    if (posEqual(t1, t2)) return 1; // same spot as we're currently on
    if (!isInLine(t1, t2)) return 2; // tile 2 not directly in line with tile 1
    if (t2.piece != 0) return 3; // tile 2 occupied already
    if (t2.attr != 0 && !(t1.piece==3)) return 4; // this is a "king only" space
    TILE temp = t1;
    while (!posEqual(temp, t2)) {
        if (isInLine(temp, t2) > 0) {
            // y must be changed
            temp.y += temp.y > t2.y ? -1 : 1;
        }
        else {
            temp.x += temp.x > t2.x ? -1 : 1;
        }
        temp = board[temp.y*11 + temp.x];
        if (temp.piece != 0) return 5; // path blocked
    }
    
    return 0; // the move is a valid move
}
TILE selectTile(TILE board[], TILE last) {
    int cmd;
    int x = last.x, y = last.y;
    do {
        jumpTo(xsp(x), ysp(y));
        cmd = getch();
        switch (cmd) {
            case 'w':
                y -= y > 0 ? 1 : -10;
                break;
            case 's':
                y += y < 10 ? 1 : -10;
                break;
            case 'a':
                x -= x > 0 ? 1 : -10;
                break;
            case 'd':
                x += x < 10 ? 1 : -10;
                break;
            case 224: // arrow key may have been pressed
                switch (getch()) {
                    case UPKEYCODE:
                        y -= y > 0 ? 1 : -10;
                        break;
                    case DOWNKEYCODE:
                        y += y < 10 ? 1 : -10;
                        break;
                    case LEFTKEYCODE:
                        x -= x > 0 ? 1 : -10;
                        break;
                    case RIGHTKEYCODE:
                        x += x < 10 ? 1 : -10;
                        break;
                }
                break;
            case 27: // escape
                printErrorString(7); // Abort game? (Y/N)
                if (getYesNo()) {
                    memset(&last, 0, sizeof last);
                    return last;
                }
                printErrorString(0); // clear "Abort game?"-prompt
                break;
        }
    } while (! (cmd == 13 || cmd == ' ')); // return key or space can be used to select tile
    return board[y*11+x];
}
void printErrorString(int errorCode) {
    int oldx = getXPos(), oldy = getYPos();
    jumpTo(0, 15);
    for (int i = 0; i < 79; i++) printf(" "); // clear line
    jumpTo(0, 15);
    switch (errorCode) {
        case 1:
            // note: N/A
            printf("You can't move to the tile you're already on!");
            break;
        case 2:
            printf("You can only move to tiles directly in line with your current tile.");
            break;
        case 3:
            printf("This tile is already occupied.");
            break;
        case 4:
            printf("Only the king can move to this tile.");
            break;
        case 5:
            printf("The path to this tile is blocked by a different piece.");
            break;
        case 6:
            printf("You must select one of your own pieces.");
            break;
        case 7:
            printf("Abort game? (Y/N)");
    }
    jumpTo(oldx, oldy);
}
void makeMove(TILE t1, TILE t2, TILE board[]) {
    board[getIndex(t2)].piece = t1.piece;
    board[getIndex(t1)].piece = 0;
    for (int i = 0; i < 4; i++) {
        // loop over the directions
        if (hasEnemy(i, board, getIndex(t2)) > 0) {
            TILE r = getRelativeTile(i, board[getIndex(t2)], board);
            if (hasEnemy(i, board, getIndex(r)) > 0 && r.piece != 3) {
                board[getIndex(r)].piece = 0;
            }
        }
    }
}
char hasWinner(TILE board[], TILE last) {
    if (last.attr == 1) return 2;
    
    int i;
    for (i = 0; i < 11*11; i++) {
        if (board[i].piece==3) break;
    }
    if (hasEnemy(LEFT, board, i) && hasEnemy(RIGHT, board, i) &&
        hasEnemy(UP, board, i) && hasEnemy(DOWN, board, i)) {
        if (bordersKing(last, board[i])) {
            return 1;
        }
    }
    return 0;
}