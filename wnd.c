#include "wnd.h"
#include <windows.h>
#include <conio.h>

WORD setAttribute(WORD attr) {
    CONSOLE_SCREEN_BUFFER_INFO coninfo;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsole, &coninfo);
    SetConsoleTextAttribute(hConsole, attr);
    return coninfo.wAttributes; // return the original attributes
}
void jumpTo(int x, int y) {
    CONSOLE_SCREEN_BUFFER_INFO coninfo;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsole, &coninfo);
    coninfo.dwCursorPosition.X = x;
    coninfo.dwCursorPosition.Y = y;
    SetConsoleCursorPosition(hConsole, coninfo.dwCursorPosition);
}
int getXPos() {
    CONSOLE_SCREEN_BUFFER_INFO coninfo;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsole, &coninfo);
    return coninfo.dwCursorPosition.X;
}
int getYPos() {
    CONSOLE_SCREEN_BUFFER_INFO coninfo;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsole, &coninfo);
    return coninfo.dwCursorPosition.Y;
}
char getYesNo() {
    int cmd;
    do {
        cmd = getch();
    } while (!(cmd == 'y' || cmd == 'Y' || cmd == 'n' || cmd == 'N'));
    return cmd == 'y' || cmd == 'Y';
}