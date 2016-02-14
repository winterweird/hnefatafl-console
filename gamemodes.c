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
        printf("%s, make a move!\n", currentPlayer==1?"Attacker":"Defender");
        printBoard(board);
        int r;
        t = selectPiece(board, currentPlayer, t);
        if (tileEmpty(t)) return 0;
        printIntense(t);
        g = selectNewPosition(board, t, &r);
        if (tileEmpty(g)) return 0;
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

static void initTutorialBoard(TILE board[], char state) {
    for (int i = 0; i < 11*11; i++) {
        char y = i / 11, x = i % 11;
        board[i].x = x;
        board[i].y = y;
        board[i].piece = 0;
        board[i].attr = state == 0 || state > 4 ? 0 : 3;
    }
    if (state==0) {
        // moving a piece
        board[5*11+5].piece = 1;
    }
    else if (state==1) {
        // capturing a piece
        board[4*11+6].piece = 2;
        board[4*11+7].piece = 1;
        board[5*11+5].piece = 1;
        board[4*11+5].attr = 0; // allowed to go here
    }
    else if (state==2) {
        // moving into being flanked
        board[4*11+5].piece = 2;
        board[3*11+3].piece = 1;
        board[5*11+3].piece = 1;
        board[4*11+3].attr = 0; // allowed to go here
    }
    else if (state==3) {
        // capturing the king
        board[3*11+5].piece = 1;
        board[7*11+5].piece = 1;
        board[4*11+4].piece = 1;
        board[4*11+6].piece = 1;
        board[4*11+5].piece = 3;
        board[5*11+5].attr = 0; // allowed to go here
    }
    else if (state==4) {
        // capturing the king while he's up against a wall
        board[4*11+10].piece = 3;
        board[4*11+9].piece = 1;
        board[5*11+10].piece = 1;
        board[3*11+6].piece = 1;
        board[3*11+10].attr = 0; // allowed to go here
    }
    else if (state==5) {
        // getting the king to an exit
        board[5*11+5].piece = 3;
        board[0].attr = 1;
        board[10].attr = 1;
        board[10*11].attr = 1;
        board[10*11+10].attr = 1;
    }
    else if (state==6) {
        // moving the king to the home tile
        board[5*11+7].piece = 3;
        board[5].piece = 2;
        board[0].attr = 1;
        board[10].attr = 1;
        board[10*11].attr = 1;
        board[10*11+10].attr = 1;
        board[5*11+5].attr = 2;
    }
    else if (state==7) {
        // capturing using a special tile as a partner
        board[10*11+9].piece = 3;
        board[10*11+7].piece = 1;
        board[6*11+5].piece = 2;
        board[9*11+5].piece = 1;
        board[0].attr = 1;
        board[10].attr = 1;
        board[10*11].attr = 1;
        board[10*11+10].attr = 1;
        board[5*11+5].attr = 2;
    }
    else {
        printf("State not implemented: %d\n", state);
        exit(1);
    }
}

void tutorial() {
    printf("Hnefatafl (also called Viking chess, King's Table, etc.) is a board game\n");
    printf("with two unequal sides; the attackers, whose goal is to capture the king\n");
    printf("by surrounding him, and the defenders, whose goal is to get their king to\n");
    printf("safety by moving him to one of the exits situated in each corner.\n\n");
    
    pauseForKeyPress();
    
    printf("The players alternate turns of moving a single piece. The pieces can move\n");
    printf("like rooks in chess, and capture by... you know what, it'd be easier to\n");
    printf("just show you.\n\n");
    
    pauseForKeyPress();
    
    TILE board[121];
    TILE a = {0}, b;
    int r;
    initTutorialBoard(board, 0);
    system("cls");
    jumpTo(0,17);
    printf("Select the piece on the board and move it horizontally or vertically.\n");
    printf("You can move the cursor with the arrow keys or W, A, S and D, and you can\n");
    printf("select a space on the board using the spacebar or Enter button.\n\n");
    printf("Note how the piece lights up with a more intense white once selected.");
    do {
        jumpTo(0,1);
        printBoard(board);
        a = selectPiece(board, 1, a);
        printIntense(a);
        b = selectNewPosition(board, a, &r);
        if (r) continue;
        makeMove(a, b, board);
        a = b;
    } while (board[60].piece);
    
    system("cls");
    jumpTo(0,1);
    printBoard(board);
    initTutorialBoard(board, 1);
    jumpTo(0,17);
    printf("Good! "); pauseForKeyPress();
    printf("Now it's time to learn how to capture. Pieces in this game can\n");
    printf("be captured if they are surrounded on two opposite sides. Move the\n");
    printf("attacking piece in place in order to capture the defending piece.\n\n");
    printf("If you select the wrong piece by accident, you can select it again to\n");
    printf("remove the selection.");
    do {
        jumpTo(0,1);
        printBoard(board);
        a = selectPiece(board, 1, a);
        printIntense(a);
        b = selectNewPosition(board, a, &r);
        if (r) continue;
        makeMove(a, b, board);
        a = b;
    } while (board[60].piece);
    
    system("cls");
    jumpTo(0,1);
    printBoard(board);
    initTutorialBoard(board, 2);
    jumpTo(0,17);
    printf("There you go! "); pauseForKeyPress();
    printf("However, if a player voluntarily moves his own piece into a situation\n");
    printf("where it is surrounded, the piece isn't captured.\n\n");
    printf("Move the defending piece in between the two attacking ones to observe this.");
    do {
        jumpTo(0,1);
        printBoard(board);
        a = selectPiece(board, 2, a);
        printIntense(a);
        b = selectNewPosition(board, a, &r);
        if (r) continue;
        makeMove(a, b, board);
        a = b;
    } while (board[47].piece != 2);
    
    system("cls");
    jumpTo(0,1);
    printBoard(board);
    initTutorialBoard(board, 3);
    jumpTo(0,17);
    printf("Well done! Notice how the piece wasn't captured. "); pauseForKeyPress();
    printf("The king needs to be surrounded by four pieces to be captured. If\n");
    printf("the attackers capture the king, they win the game.");
    do {
        jumpTo(0,1);
        printBoard(board);
        a = selectPiece(board, 1, a);
        printIntense(a);
        b = selectNewPosition(board, a, &r);
        if (r) continue;
        makeMove(a, b, board);
        a = b;
    } while (board[82].piece);
    
    system("cls");
    jumpTo(0,1);
    printBoard(board);
    initTutorialBoard(board, 4);
    jumpTo(0,17);
    printf("Success! "); pauseForKeyPress();
    printf("In the event that the king is up against the wall, he only needs to\n");
    printf("be surrounded on the three available tiles around him.");
    do {
        jumpTo(0,1);
        printBoard(board);
        a = selectPiece(board, 1, a);
        printIntense(a);
        b = selectNewPosition(board, a, &r);
        if (r) continue;
        makeMove(a, b, board);
        a = b;
    } while (board[39].piece);
    
    system("cls");
    jumpTo(0,1);
    printBoard(board);
    initTutorialBoard(board, 5);
    jumpTo(0,17);
    printf("Great! Next up, special tiles. "); pauseForKeyPress();
    printf("There are four exits in the game, one in each corner of the board. The\n");
    printf("goal of the defending player is to get the king to one of these exits.\n");
    printf("If the king gets to safety, the defenders win the game.\n\n");
    printf("Move the king to one of the exits. You need to reselect it for each move.");
    do {
        jumpTo(0,1);
        printBoard(board);
        a = selectPiece(board, 2, a);
        printIntense(a);
        b = selectNewPosition(board, a, &r);
        if (r) continue;
        makeMove(a, b, board);
        a = b;
    } while (!(getIndex(b)==0 || getIndex(b)==10 || getIndex(b)==10*11 || getIndex(b)==10*11+10));
    
    system("cls");
    jumpTo(0,1);
    printBoard(board);
    initTutorialBoard(board, 6);
    jumpTo(0,17);
    printf("Good job! "); pauseForKeyPress();
    printf("Only the king can be moved to the exits. In addition, the center spot\n");
    printf("where the king is positioned at the beginning of the game can also only\n");
    printf("be occupied by the king.\n\n");
    printf("If you try to move the other piece onto the home tile or one of the exit\n");
    printf("tiles, you'll see that this isn't allowed. Move the king to the home tile\n");
    printf("to proceed.");
    do {
        jumpTo(0,1);
        printBoard(board);
        a = selectPiece(board, 2, a);
        printIntense(a);
        b = selectNewPosition(board, a, &r);
        if (r) continue;
        makeMove(a, b, board);
        a = b;
    } while (!(getIndex(b)==60));
    
    system("cls");
    jumpTo(0,1);
    printBoard(board);
    initTutorialBoard(board, 7);
    jumpTo(0,17);
    printf("Fantastic! "); pauseForKeyPress();
    printf("Furthermore, the exits and the home tile can be used as capture partners.\n");
    printf("In other words, a piece standing next to one of these tiles is extra\n");
    printf("vulnerable because it's like being half surrounded already.\n\n");
    printf("Capture the defending soldier and then the king to proceed.");
    do {
        jumpTo(0,1);
        printBoard(board);
        a = selectPiece(board, 1, a);
        printIntense(a);
        b = selectNewPosition(board, a, &r);
        if (r) continue;
        makeMove(a, b, board);
        a = b;
    } while (board[6*11+5].piece || !(board[9*11+9].piece && board[10*11+8].piece));
    
    system("cls");
    jumpTo(0,1);
    printBoard(board);
    initTutorialBoard(board, 7);
    jumpTo(0,17);
    printf("Congratulations! This marks the end of the tutorial. Please remember,\n");
    printf("however, that when you're playing the actual game, it won't constantly be\n");
    printf("your turn (duh). You also won't be denied the opportunity of making bad\n");
    printf("decisions. So think before you move, m'kay?\n\n");
    
    pauseForKeyPress();
}