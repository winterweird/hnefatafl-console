#include "board.h"
#include "wnd.h"
#include <stdio.h>
//#include <conio.h>

#define WHITE FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE
#define INTENSE FOREGROUND_INTENSITY

#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

const char pieceChar[] = " xoK";
const char attrChar[] = " EH";

void initBoard(TILE board[]) {
    char p[121] = {
        0,0,0,1,1,1,1,1,0,0,0,
        0,0,0,0,0,1,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,
        1,0,0,0,0,2,0,0,0,0,1,
        1,0,0,0,2,2,2,0,0,0,1,
        1,1,0,2,2,3,2,2,0,1,1,
        1,0,0,0,2,2,2,0,0,0,1,
        1,0,0,0,0,2,0,0,0,0,1,
        0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,1,0,0,0,0,0,
        0,0,0,1,1,1,1,1,0,0,0
    };
    board[0].attr = 1;
    board[10].attr = 1;
    board[110].attr = 1;
    board[120].attr = 1;
    board[60].attr = 2;
    for (int i = 0; i < 11*11; i++) {
        char y = i / 11, x = i % 11;
        board[i].x = x;
        board[i].y = y;
        board[i].piece = p[i];
    }
}
int getIndex(TILE t) {
    return t.y*11+t.x;
}
int xsp(int x) {
    return x*2+1;
}
int ysp(int y) {
    return y+2;
}
void printBoard(TILE board[]) {
    printf("-----------------------\n");
    for (int i = 0; i < 11*11; i++) {
        i%11==0?printf("|"):0;
        printf("%c%s", board[i].piece ? pieceChar[board[i].piece] : attrChar[board[i].attr], i%11==10?"|\n":" ");
    }
    printf("-----------------------\n");
}
void printIntense(TILE t) {
    setAttribute(setAttribute(INTENSE|WHITE)*printf("%c", t.piece?pieceChar[t.piece]:attrChar[t.attr]));
}
TILE getRelativeTile(int dir, TILE t, TILE board[]) {
    switch (dir) {
        case LEFT:
            t.x--;
            break;
        case RIGHT:
            t.x++;
            break;
        case UP:
            t.y--;
            break;
        case DOWN:
            t.y++;
            break;
    }
    return board[getIndex(t)];
}