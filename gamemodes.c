#include "gamemodes.h"
#include "board.h"
#include "wnd.h"
#include "logic.h"
#include <stdio.h>

int localGame() {
    system("cls");
    char winner = 0;
    TILE board[121];
    memset(&board, 0, sizeof board);
    initBoard(board);
    char currentPlayer = 1;
    TILE t = {0,0,0,0}, g;
    do {
        jumpTo(0,0);
        printf("Player %d, make a move!\n", currentPlayer);
        printBoard(board);
        int r;
        do {
            t = selectTile(board, t);
            if (tileEmpty(t)) return 0;
            printErrorString(ownsPiece(currentPlayer, t) ? 0 : 6);
        } while (!ownsPiece(currentPlayer, t));
        printIntense(t);
        do {
            g = selectTile(board, t);
            if (tileEmpty(g)) return 0;
            r = moveValidity(t, g, board);
            if (r==1) break;
            printErrorString(r);
        } while (r != 0);
        if (r) continue;
        makeMove(t, g, board);
        winner = hasWinner(board, board[getIndex(g)]);
        currentPlayer = currentPlayer % 2 + 1;
        t = g;
    } while (!winner);
    
    // reblit board to capture last move
    jumpTo(0,1);
    printBoard(board);
    return winner;
}