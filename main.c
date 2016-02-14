#include <stdio.h>
#include "wnd.h"
#include "gamemodes.h"
#include "menu.h"

// NOTE: A lot of the functions I've made are dependent on the order of input
// (for instance, getRelativeTile might malfunction if you call it without
// first making sure that the tile you're checking for isn't at the edge of
// the board already). Keep this in mind if you're trying to edit or extend
// the code for Hnefatafl.

int main() {
    char playing = 1;
    char reply;
    char winner;
    char who;
    while (playing) {
        who = 0;
        if (winner != -1) {
            system("cls");
            printf("WELCOME TO HNEFATAFL - CONSOLE VERSION!\n\n");
        }
        
        reply = promptMenu(6, "Single player", "2-player", "Tutorial", "Local network game", "Online game", "Exit");
        switch (reply) {
            case 0:
                printUnderMenu("Single player not currently supported.");
                winner = -1;
                break;
            case 1:
                winner = localGame();
                break;
            case 2:
                // blit out any "not supported" messages
                printUnderMenu("                                      ");
                tutorial();
                winner = -2;
                break;
            case 3:
                printUnderMenu("Local network not currently supported.");
                winner = -1;
                break;
            case 4:
                printUnderMenu("Online game not currently supported.  ");
                winner = -1;
                break;
            default:
                // will be the last option, always, hence just put "default"
                playing = 0;
        }
        if (winner > -1) {
            // handle
        }
    }
}