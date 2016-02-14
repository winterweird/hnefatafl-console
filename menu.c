#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include "wnd.h"



char promptMenu(int optnum, ...) {
    va_list ap;
    va_start(ap, optnum);
    promptMenuVL(optnum, ap);
}
char printUnderMenu(const char* str) {
    jumpTo(0, 5);
    printf("%s", str);
    jumpTo(0, 2);
}

char promptMenuVL(int optnum, va_list ap) {
    // DISCLAIMER: I wrote this a while back, and now I don't remember how it
    // works anymore. It's a black box to me. Don't hate me for it.
    
    // assumption: You start at the beginning at the line from which you want
    // to start laying out the menu of choices
    CONSOLE_SCREEN_BUFFER_INFO sbi = getSBI();
    
    COORD* posList = malloc(optnum * sizeof *posList);
    const char** optionStrings = malloc(optnum * sizeof *optionStrings);
    int longestStrLen = 0;
    int i;
    // map option texts
    for (i = 0; i < optnum; i++) {
        optionStrings[i] = va_arg(ap, const char*);
        longestStrLen = strlen(optionStrings[i]) > longestStrLen ? strlen(optionStrings[i]) : longestStrLen;
    }
    // map option positions in the console
    for (i = 0; i < optnum; i++) {
        COORD currentPos = {getXPos(), getYPos()};
        posList[i] = currentPos;
        int x, y;
        x = currentPos.X + 2*longestStrLen+3 >= sbi.dwSize.X-1 ? 0 : currentPos.X + longestStrLen+3;
        y = currentPos.X + 2*longestStrLen+3 >= sbi.dwSize.X-1 ? currentPos.Y+1 : currentPos.Y;
        jumpTo(x, y);
        // ternary condition: If you could put the longest string + 3 spaces
        // next to where you are now, put the next string next to your current
        // position - else, put it at the beginning of the next line
    }
    
    // print the menu and get the actual input
    int input; // change to 0 when you wanna exit
    // the following three will be nice to know when keyboard input
    int optionsPerLine = (sbi.dwSize.X-1) / (longestStrLen+3) > optnum ? optnum : (sbi.dwSize.X-1) / (longestStrLen+3);
    int nOfLines = ceil(optnum / (float)optionsPerLine);
    int currentIndex = 0;
    do {
        for (i = 0; i < optnum; i++) {
            jumpTo(posList[i].X, posList[i].Y);
            i == currentIndex ? printStringIntense(optionStrings[i]) : printf("%s", optionStrings[i]);
        }
        input = getch();
        switch(input) {
            case ' ':
            case 13: // return key
                // jump down two lines from the last line of options
                jumpTo(0, posList[optnum-1].Y+2);
                input = 0; // exit loop
                break;
            case 'w':
                input = 72;
                goto ARROWKEY;
            case 'a':
                input = 75;
                goto ARROWKEY;
            case 's':
                input = 80;
                goto ARROWKEY;
            case 'd':
                input = 77;
                goto ARROWKEY;
            case 224: // arrow key pressed
                input = getch();
                ARROWKEY:
                switch(input) {
                    case 72: // up
                        currentIndex -= currentIndex-optionsPerLine >= 0 ? optionsPerLine : 0;
                        break;
                    case 80: // down
                        currentIndex += currentIndex+optionsPerLine < optnum ? optionsPerLine : 0;
                        break;
                    case 75: // left
                        currentIndex = optionsPerLine*(currentIndex / optionsPerLine) + (currentIndex-1) % optionsPerLine;
                        //currentIndex -= (currentIndex-1) >= 0 ? 1 : 0;
                        while (currentIndex > optnum-1) currentIndex--;
                        break;
                    case 77: // right
                        currentIndex = optionsPerLine*(currentIndex / optionsPerLine) + (currentIndex+1) % optionsPerLine;
                        //currentIndex += (currentIndex+1) < optnum ? 1 : 0;
                        break;
                }
                break;
            // default: break;
        }
        if(currentIndex > optnum-1) {
            currentIndex = 0 + optionsPerLine*(nOfLines-1);
        }
        else if(currentIndex < 0) {
            currentIndex = optionsPerLine-1;
        }
    } while(input);
    return currentIndex;
}