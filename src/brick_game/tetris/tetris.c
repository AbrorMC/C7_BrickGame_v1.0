#include "tetris.h"

static GameInfo_t game;

int main()
{
    WIN_INIT();
    setlocale(LC_ALL, "");

    printOverlay();

    bool breakFlag = true;
    int signal = 0;
    clock_t lastDropTime = clock();

    initGame();

    Params_t prms;
    prms.game = &game;
    prms.state = START;

    halfdelay(10);

    while (breakFlag)
    {
        if (prms.state == GAMEOVER || prms.state == EXIT_STATE)
            breakFlag = FALSE;

        clock_t currentTime = clock();

        if (currentTime - lastDropTime > DROP_INTERVAL &&
            prms.state != START && prms.state != SPAWN && prms.state != ATTACHING)
        {
            lastDropTime = currentTime;
            signal = Up;
            prms.state = SHIFTING;
        }

        UserAction_t curAction = getAction(signal);
        userInput(curAction, &prms, false);

        if (prms.state == MOVING || prms.state == START)
            signal = getch();
    }

    removeMatrix(game.field, BOARD_HEIGHT);
    nodelay(stdscr, FALSE);
    getch();
    endwin();

    return 0;
}

void initGame()
{
    game.field = initMatrix(BOARD_HEIGHT, BOARD_WIDTH);
    game.next = initMatrix(2, 4);
    game.level = 1;
    game.score = 1;
    game.speed = 1;
    game.pause = 0;
    game.high_score = 0;
}
