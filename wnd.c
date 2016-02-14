#include "wnd.h"
#include <windows.h>
#include <conio.h>
#include <stdio.h>

#define WHITE FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE
#define INTENSE FOREGROUND_INTENSITY

CONSOLE_SCREEN_BUFFER_INFO getSBI() {
    CONSOLE_SCREEN_BUFFER_INFO coninfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);
    return coninfo;
}

WORD setAttribute(WORD attr) {
    CONSOLE_SCREEN_BUFFER_INFO coninfo = getSBI();
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attr);
    return coninfo.wAttributes; // return the original attributes
}
void jumpTo(int x, int y) {
    CONSOLE_SCREEN_BUFFER_INFO coninfo = getSBI();
    coninfo.dwCursorPosition.X = x;
    coninfo.dwCursorPosition.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coninfo.dwCursorPosition);
}
int getXPos() {
    CONSOLE_SCREEN_BUFFER_INFO coninfo = getSBI();
    return coninfo.dwCursorPosition.X;
}
int getYPos() {
    CONSOLE_SCREEN_BUFFER_INFO coninfo = getSBI();
    return coninfo.dwCursorPosition.Y;
}
char getYesNo() {
    int cmd;
    do {
        cmd = getch();
    } while (!(cmd == 'y' || cmd == 'Y' || cmd == 'n' || cmd == 'N'));
    return cmd == 'y' || cmd == 'Y';
}
void pauseForKeyPress() {
    printf("Press a key to continue.");
    getch();
    jumpTo(0, getYPos());
    for (int i = 0; i < 79; i++) printf(" ");
    jumpTo(0, getYPos());
}
void printStringIntense(const char* str) {
    // none of you idiots will know to appreciate the effort I put into making
    // this a one-liner in this manner
    setAttribute((setAttribute(INTENSE|WHITE)*1) * (printf("%s", str) > -1));
}