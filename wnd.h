#ifndef WND_H
#define WND_H

#include <windows.h>

WORD setAttribute(WORD); // set new text attribute and return the old one
void jumpTo(int, int);   // jump to the coordinate in the console specified by x, y
int getXPos();           // return the X value of the console cursor coordinate
int getYPos();           // return the Y value of the console cursor coordinate
char getYesNo();         // prompt until user inputs Y/N (case insensitive) and return input=='y'

#endif /* WND_H */