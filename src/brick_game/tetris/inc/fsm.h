#ifndef FSM_H
#define FSM_H

#include <ncurses.h>
#include "define.h"
#include "objects.h"
#include "backend.h"
#include "frontend.h"

typedef enum
{
    START = 0,
    SPAWN,
    MOVING,
    SHIFTING,
    ATTACHING,
    PAUSE,
    GAMEOVER,
    EXIT_STATE
} State_t;

typedef enum
{
    Start = 0,
    Pause,
    Terminate,
    Left,
    Right,
    Action,
    Down,
    Up
} UserAction_t;

typedef struct
{
    int **field;
    int **next;
    int score;
    int high_score;
    int level;
    int speed;
    int pause;
} GameInfo_t;

typedef struct
{
    GameInfo_t *game;
    State_t state;
    Shape_t *shape;
    Shape_t *nextSh;
    bool *break_flag;
} Params_t;

UserAction_t getAction(int user_input);
void userInput(UserAction_t action, Params_t *prms, bool hold);

void exitState(Params_t *params);
void spawn(Params_t *params);
void shifting(Params_t *params);
void moveLeft(Params_t *params);
void moveRight(Params_t *params);
void check(Params_t *params);
void pause(Params_t *params);
void rotate(Params_t *params);
void moveDown(Params_t *params);
void attaching(Params_t *params);
void goOn(Params_t *params);
void gameover(Params_t *params);

bool isRotatable(Params_t *params);

#endif