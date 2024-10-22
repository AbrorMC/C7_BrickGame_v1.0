#include "fsm.h"

typedef void (*action)(Params_t *params);

action fsm_table[8][8] = {
    {spawn, NULL, exitState, NULL, NULL, NULL, NULL, spawn},
    {spawn, pause, exitState, spawn, spawn, spawn, spawn, spawn},
    {check, pause, exitState, moveLeft, moveRight, rotate, moveDown, check},
    {shifting, pause, exitState, shifting, shifting, shifting, shifting, shifting},
    {attaching, pause, exitState, attaching, attaching, attaching, attaching, attaching},
    {goOn, goOn, exitState, goOn, goOn, goOn, goOn, goOn},
    {gameover, gameover, gameover, gameover, gameover, gameover, gameover, gameover},
    {exitState, exitState, exitState, exitState, exitState, exitState, exitState}};

void userInput(UserAction_t curAction, Params_t *prms, bool hold)
{
    action act = NULL;

    act = fsm_table[prms->state][curAction];

    if (act)
        act(prms);
}

UserAction_t getAction(int user_input)
{
    UserAction_t rc = Up;

    if (user_input == KEY_DOWN)
        rc = Down;
    else if (user_input == KEY_LEFT)
        rc = Left;
    else if (user_input == KEY_RIGHT)
        rc = Right;
    else if (user_input == SPACE)
        rc = Pause;
    else if (user_input == ENTER_KEY)
        rc = Start;
    else if (user_input == ESCAPE)
        rc = Terminate;
    else if (user_input == ROTATE_KEY)
        rc = Action;

    return rc;
}

void shifting(Params_t *params)
{
    if (checkTouch(params->shape, params->game->field, Up))
    {
        params->state = ATTACHING;
    }
    else
    {
        eraseShapeFromField(params->shape, params->game->field);
        for (int i = 0; i < 4; i++)
        {
            params->shape->blocks[i].y++;
        }
        addShapeToField(params->shape, params->game->field);
        printField(params->game->field);
        params->state = MOVING;
    }
}

void spawn(Params_t *params)
{
    Shape_t *curShape = malloc(sizeof(Shape_t));
    Shape_t *nextShape = malloc(sizeof(Shape_t));

    if (params->state == START)
    {
        *curShape = createShape();
        params->shape = curShape;
    }
    else
    {
        *curShape = *(params->nextSh);
        params->shape = params->nextSh;
    }

    *nextShape = createShape();
    params->nextSh = nextShape;

    addShapeToField(curShape, params->game->field);
    printField(params->game->field);

    shapeToMarix(nextShape, params->game->next);
    eraseNextField();
    printNextField(params->game->next);

    params->state = MOVING;
}

void moveLeft(Params_t *params)
{
    if (!checkTouch(params->shape, params->game->field, Left))
    {
        eraseShapeFromField(params->shape, params->game->field);
        for (int i = 0; i < 4; i++)
        {
            params->shape->blocks[i].x--;
        }
        addShapeToField(params->shape, params->game->field);
        printField(params->game->field);
    }
}

void moveRight(Params_t *params)
{
    if (!checkTouch(params->shape, params->game->field, Right))
    {
        eraseShapeFromField(params->shape, params->game->field);
        for (int i = 0; i < 4; i++)
        {
            params->shape->blocks[i].x++;
        }
        addShapeToField(params->shape, params->game->field);
        printField(params->game->field);
    }
}

void check(Params_t *params)
{
    params->state = SHIFTING;
}

void pause(Params_t *params)
{
    params->game->pause = 1;
    params->state = PAUSE;
    getchar();
}

void rotate(Params_t *params)
{
    Shape_t oldShape = *params->shape;
    if (isRotatable(params))
    {
        eraseShapeFromField(&oldShape, params->game->field);
        addShapeToField(params->shape, params->game->field);
        printField(params->game->field);
    }
}

void moveDown(Params_t *params)
{
    Cells_t extremeCells = initCells();
    getExtremeCells(&extremeCells, params->shape, Up);
    int pixels = getPixelsToDown(&extremeCells, params->game->field);
    Shape_t oldShape = *params->shape;
    for (int i = 0; i < 4; i++)
    {
        params->shape->blocks[i].y += pixels;
    }
    eraseShapeFromField(&oldShape, params->game->field);
    addShapeToField(params->shape, params->game->field);
    printField(params->game->field);
}

void attaching(Params_t *params)
{
    int index = BOARD_HEIGHT - 1;
    int **tempField = initMatrix(BOARD_HEIGHT, BOARD_WIDTH);
    int *rows = getFilledRows(params->game->field);

    for (int i = BOARD_HEIGHT - 1; i >= 0; i--)
    {
        if (rows[i] == 0)
        {
            for (int j = 0; j < BOARD_WIDTH; j++)
                tempField[index][j] = params->game->field[i][j];
            index--;
        }
    }

    free(rows);
    params->game->field = tempField;
    params->state = SPAWN;
}

void goOn(Params_t *params)
{
    params->state = MOVING;
}

void gameover(Params_t *params)
{
}

void exitState(Params_t *params)
{
    params->state = EXIT_STATE;
}

bool isRotatable(Params_t *params)
{
    Shape_t *shape = params->shape;
    int **field = params->game->field;

    int shiftX = 0;
    bool result = true;
    Shape_t tempShape = *shape;

    for (int i = 0; i < 4; i++)
    {
        Coor_t rotatedBlock = getRotatedCoords(shape, i);

        if (rotatedBlock.x < 0)
            shiftX = max(shiftX, -rotatedBlock.x);
        else if (rotatedBlock.x >= BOARD_WIDTH)
            shiftX = min(shiftX, BOARD_WIDTH - rotatedBlock.x - 1);

        tempShape.blocks[i] = rotatedBlock;
    }

    if (shiftX != 0)
    {
        for (int i = 0; i < 4; i++)
            tempShape.blocks[i].x += shiftX;
    }

    for (int i = 0; i < 4; i++)
    {
        Coor_t rotatedBlock = tempShape.blocks[i];

        if ((rotatedBlock.y >= BOARD_HEIGHT || field[rotatedBlock.y][rotatedBlock.x] == 1) &&
            !contains(shape, rotatedBlock))
        {
            result = false;
            break;
        }
    }

    if (result)
    {
        *shape = tempShape;
    }

    return result;
}
