#include "fsm.h"

void printRectangle(int top, int bottom, int right, int left);
void printField(int **field);

void printOverlay(void)
{
    printRectangle(0, BOARD_HEIGHT + 1, 0, BOARD_WIDTH + 1);
    printRectangle(0, BOARD_HEIGHT + 1, BOARD_WIDTH + 2, BOARD_WIDTH + HUD_WIDTH + 3);

    printRectangle(1, 4, BOARD_WIDTH + 3, BOARD_WIDTH + HUD_WIDTH + 2);
    printRectangle(5, 7, BOARD_WIDTH + 3, BOARD_WIDTH + HUD_WIDTH + 2);
    printRectangle(8, 10, BOARD_WIDTH + 3, BOARD_WIDTH + HUD_WIDTH + 2);
    printRectangle(11, 14, BOARD_WIDTH + 3, BOARD_WIDTH + HUD_WIDTH + 2);

    MVPRINTW(2, BOARD_WIDTH + 5, "HIGH");
    MVPRINTW(3, BOARD_WIDTH + 5, "SCORE");
    MVPRINTW(6, BOARD_WIDTH + 5, "SCORE");
    MVPRINTW(9, BOARD_WIDTH + 5, "LEVEL");
    MVPRINTW(12, BOARD_WIDTH + 5, "NEXT");

    // MVPRINTW(BOARD_N / 2, (BOARD_M - INTRO_MESSAGE_LEN) / 2 + 1, INTRO_MESSAGE);
    refresh();
}

void printField(int **field)
{
    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            if (field[i][j] == 1)
                MVADDCH(i + BOARDS_BEGIN, j + BOARDS_BEGIN, '*');
            else
                MVADDCH(i + BOARDS_BEGIN, j + BOARDS_BEGIN, ' ');
        }
    }
    refresh();
}

void printNextField(int **field)
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (field[i][j] == 1)
                MVADDCH(i + 12, j + BOARD_WIDTH + HUD_WIDTH / 2 + 2, '*');
        }
    }
    refresh();
}

void eraseNextField()
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            MVADDCH(i + 12, j + BOARD_WIDTH + HUD_WIDTH / 2 + 2, ' ');
        }
    }
    refresh();
}

void printRectangle(int top_y, int bottom_y, int left_x, int right_x)
{
    MVADDCH(top_y, left_x, ACS_ULCORNER);

    for (int i = left_x + 1; i < right_x; i++)
        MVADDCH(top_y, i, ACS_HLINE);
    MVADDCH(top_y, right_x, ACS_URCORNER);

    for (int j = top_y + 1; j < bottom_y; j++)
    {
        MVADDCH(j, left_x, ACS_VLINE);
        MVADDCH(j, right_x, ACS_VLINE);
    }

    MVADDCH(bottom_y, left_x, ACS_LLCORNER);

    for (int i = left_x + 1; i < right_x; i++)
        MVADDCH(bottom_y, i, ACS_HLINE);
    MVADDCH(bottom_y, right_x, ACS_LRCORNER);
    refresh();
}
