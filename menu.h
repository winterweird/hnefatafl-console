#ifndef MENU_H
#define MENU_H

#include <stdarg.h>

char promptMenu(int, ...);
char promptMenuVL(int, va_list);
char printUnderMenu(const char*);

#endif /* MENU_H */