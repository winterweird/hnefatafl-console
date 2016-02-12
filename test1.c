#include <stdio.h>
#include "wnd.h"
#include "gamemodes.h"

// NOTE: A lot of the functions I've made are dependent on the order of input
// (for instance, getRelativeTile might malfunction if you call it without
// first making sure that the tile you're checking for isn't at the edge of
// the board already). Keep this in mind if you're trying to edit or extend
// the code for Hnefatafl.

int main() {
    char playing = 1;
    while (playing) {
        int res = localGame();
        jumpTo(0, 15);
        printf(res?"Player %d is the winner!\n":"There was no winner of the previous game.\n", res);
        printf("Play again? (Y/N)\n");
        playing = getYesNo();
    }
    
}