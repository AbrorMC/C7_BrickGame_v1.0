#ifndef DEFINES_H
#define DEFINES_H

#include <stdio.h>
#include <ncurses.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define WIN_INIT()            \
    {                         \
        initscr();            \
        noecho();             \
        curs_set(0);          \
        keypad(stdscr, TRUE); \
    }

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))
#define MVPRINTW(y, x, ...) mvprintw(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x), __VA_ARGS__)

#define ESCAPE 27
#define ENTER_KEY 10
#define SPACE 32
#define ROTATE_KEY 9

#define DROP_INTERVAL 1000

#define BOARDS_BEGIN 1
#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20
#define HUD_WIDTH 18
#define SHAPES_COUNT 7
#define MVADDCH(y, x, c) mvaddch(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x), c)

#endif