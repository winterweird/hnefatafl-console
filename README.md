### Update, 2016/02/14:
The game now includes a menu interface and an in-game tutorial. In other words, there's no need to read the rules here anymore - you can follow the tutorial and learn by doing!

# Hnefatafl in the Windows console

## SCREENSHOTS:
![The initial setup](http://puu.sh/n5nZd/328a226219.jpg)
![Defender piece ready to capture](http://puu.sh/n5o1w/7504563734.png)
![Defender piece has captured](http://puu.sh/n5o5j/785f1f23c2.png)
![Attacker got an easy victory](http://puu.sh/n5oaE/eb1852560b.png)

## Description:

Hnefatafl is the precedent of chess in Europe, dating back to around 800 AD. In this board game, you play as one of two sides - the defenders, whose goal is to get their king to safety, and the attackers, whose goal is to capture the king by surrounding him.

The gameplay itself is pretty simple. This version is played out on an 11x11 grid, although there are versions which are played on a 9x9 or even a 7x7 grid. The pieces move like rooks in chess, in other words horizontally or vertically. The players alternate turns of moving a single piece, starting with the attackers (x).

Pieces can be captured by flanking them on two opposite sides, (e.g. to the left and to the right, or up and down). However, if a player moves his own piece into a flanked situation, the piece is not captured. Whereas normal pieces (x, o) only need to be flanked on two sides, the king (K) needs to be surrounded on all four sides - or three, if he is positioned by the edge. In addition, the exits in the corners (E) and the center field where the king is initially positioned (H) can only be entered by the king, and also function as capture partners. In other words, if the king is standing right next to an exit, he only needs to be surrounded on the two sides which the enemy pieces can reach. Normal pieces standing next to an exit or the center field only need to be flanked on the opposite side to be captured.

In practice, the game works through a two-phase tile selection model where the player navigates the board using the arrow keys or WASD controls. When the player has found the piece he/she wants to move, it can be selected with either the spacebar or the enter key. The selected piece lights up with a bright white color, and the player selects the tile he/she wishes to move it to. If the player selects the same tile as in the previous step, he/she is returned to step 1 and allowed to select another piece. When the piece has been moved, the turn passes to the next player. If any player presses the escape button, they will be prompted with whether they want to abort the current game - entering "Y" will end the game with no winner, whereas entering "N" will resume the game.

## Notes on running / building the game:

This game works as compiled on a Windows 7 PC using MinGW GCC v4.8.1. It utilizes Windows APIs and the non-standard getch()-function, and as such probably cannot be ported to other platforms, even when using Wine on Linux. To get the game, assuming you have MinGW installed on your computer, you can download the source files and build it on your own Windows computer by opening a command prompt in the source code directory and running one of MinGW's make tools (typically "make" or similar). If you are unwilling or unable to build this game with make, reading the makefile should give you an idea of how to build the game on your own - alternatively, you may run the precompiled executable in the master folder.

## Disclaimer and afterword:

Please note that the foundation of this game was hacked together in my spare time over the course of a few days - originally in a single file, which was later split in several files in an attempt to structurize the project a little bit. Therefore, there are a bunch of messy parts, greatly helped by my general affinity for messy code constructs, one-liners, etc. I've commented my code whenever I remembered to, in other words pretty damn rarely. Enter and modify the source code at your own risk, should you be so inclined.

I wish to extend this project in the future, for example with a menu-based user interface and the addition of new game modes - including the option of playing the game over a network, and maybe even a single-player mode with an AI opponent, if I can ever be bothered to make something like that. But for the time being, this is a 2-player bare-bones version of hnefatafl 11x11, which (as far as I know) operates entirely in accordance with the rules of the game.
