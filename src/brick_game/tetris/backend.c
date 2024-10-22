#include "backend.h"
#include "fsm.h"

Shape_t shapesList[SHAPES_COUNT] = {
    I_SHAPE,
    L_SHAPE,
    O_SHAPE,
    Z_SHAPE,
    S_SHAPE,
    T_SHAPE,
    J_SHAPE};

int **initMatrix(int row, int col)
{
    int **array = (int **)malloc(row * sizeof(int *));
    for (int i = 0; i < row; i++)
    {
        array[i] = (int *)malloc(col * sizeof(int));
        for (int j = 0; j < col; j++)
            array[i][j] = 0;
    }
    return array;
}

void removeMatrix(int **matrix, int row)
{
    for (int i = 0; i < row; i++)
        free(matrix[i]);

    free(matrix);
}

void shapeToMarix(Shape_t *shape, int **field)
{
    int tempBlocks[4][2];
    for (int i = 0; i < 4; i++)
    {
        int tempX = shape->blocks[i].x;
        int tempY = shape->blocks[i].y;
        if (shape->size == 2 || i == shape->center - 1)
        {
            tempBlocks[i][0] = tempY;
            tempBlocks[i][1] = tempX;
        }
        else
        {
            tempBlocks[i][0] = shape->blocks[shape->center - 1].y - shape->blocks[shape->center - 1].x + tempX;
            tempBlocks[i][1] = shape->blocks[shape->center - 1].y + shape->blocks[shape->center - 1].x - tempY;
        }
    }
    int correction = shape->size == 2 ? 0 : (shape->size == 4 ? -1 : shape->center - 1);
    for (int i = 0; i < 4; i++)
        field[tempBlocks[i][0] - correction][tempBlocks[i][1] - BOARD_WIDTH / 2 + 1] = 1;
}

bool checkTouch(Shape_t *shape, int **field, int action)
{
    Cells_t extremeCells = initCells();
    getExtremeCells(&extremeCells, shape, action);
    bool check = checkNonEmpty(&extremeCells, field, action);
    return check;
}

bool checkNonEmpty(Cells_t *extremeCells, int **field, int action)
{
    bool check = false;
    int sideWall = action == Left ? -1 : BOARD_WIDTH;
    for (int j = 0; j < 4; j++)
    {
        if (extremeCells->blocks[j].y == -1)
            continue;
        if (action == Up)
        {
            if (extremeCells->blocks[j].y == BOARD_HEIGHT ||
                field[extremeCells->blocks[j].y][extremeCells->blocks[j].x] == 1)
            {
                check = true;
                break;
            }
        }
        else
        {
            if (extremeCells->blocks[j].x == sideWall ||
                field[extremeCells->blocks[j].y][extremeCells->blocks[j].x] == 1)
            {
                check = true;
                break;
            }
        }
    }
    return check;
}

void getExtremeCells(Cells_t *extremeCells, Shape_t *shape, int action)
{
    int directionX = action == Left ? -1 : (action == Right ? 1 : 0);
    int directionY = action == Up ? 1 : 0;
    int count = 0;
    for (int i = 0; i < 4; i++)
    {
        Coor_t temp;
        temp.x = shape->blocks[i].x + directionX;
        temp.y = shape->blocks[i].y + directionY;
        if (!contains(shape, temp))
        {
            extremeCells->blocks[count] = temp;
            count++;
        }
    }
}

Cells_t initCells()
{
    Cells_t extremeCells;

    for (int i = 0; i < 4; i++)
    {
        extremeCells.blocks[i].x = -1;
        extremeCells.blocks[i].y = -1;
    }
    return extremeCells;
}

bool contains(Shape_t *result, Coor_t cell)
{
    bool res = false;
    for (int i = 0; i < 4; i++)
    {
        if (result->blocks[i].x == cell.x && result->blocks[i].y == cell.y)
        {
            res = true;
            break;
        }
    }
    return res;
}

int generateInt(int limit)
{
    srand(time(NULL));
    int random_number = (rand() % limit);
    return random_number;
}

Shape_t createShape()
{
    // Shape_t curShape = shapesList[generateInt(SHAPES_COUNT)];
    Shape_t curShape = shapesList[1];
    initShapePosition(&curShape);
    return curShape;
}

void addShapeToField(Shape_t *shape, int **field)
{
    for (int i = 0; i < 4; i++)
    {
        int x = shape->blocks[i].x;
        int y = shape->blocks[i].y;

        if (x >= 0 && x < BOARD_WIDTH && y >= 0 && y < BOARD_HEIGHT)
        {
            field[y][x] = 1;
        }
    }
}

void eraseShapeFromField(Shape_t *shape, int **field)
{
    for (int i = 0; i < 4; i++)
    {
        int x = shape->blocks[i].x;
        int y = shape->blocks[i].y;

        if (x >= 0 && x < BOARD_WIDTH && y >= 0 && y < BOARD_HEIGHT)
        {
            field[y][x] = 0;
        }
    }
}

void initShapePosition(Shape_t *shape)
{
    for (int i = 0; i < 4; i++)
    {
        shape->blocks[i].x += BOARD_WIDTH / 2;
    }
}

Coor_t getRotatedCoords(Shape_t *shape, int i)
{
    Coor_t temp;
    if (shape->size == 2 || i == shape->center - 1)
    {
        temp.y = shape->blocks[i].y;
        temp.x = shape->blocks[i].x;
    }
    else
    {
        temp.y = shape->blocks[shape->center - 1].y - shape->blocks[shape->center - 1].x +
                 shape->blocks[i].x;
        temp.x = shape->blocks[shape->center - 1].y + shape->blocks[shape->center - 1].x -
                 shape->blocks[i].y;
    }

    return temp;
}

int getPixelsToDown(Cells_t *extremeCells, int **field)
{
    int result = BOARD_HEIGHT;
    for (int i = 0; i < 4; i++)
    {
        if (extremeCells->blocks[i].y == -1)
            continue;

        int count = 0;
        for (int j = extremeCells->blocks[i].y; j < BOARD_HEIGHT; j++)
        {
            if (!field[j][extremeCells->blocks[i].x])
                count++;
            else
                break;
        }
        if (count <= result)
            result = count;
    }
    return result;
}

int *getFilledRows(int **field)
{
    int *rows = (int *)malloc(BOARD_HEIGHT * sizeof(int));
    if (rows == NULL)
        return NULL;

    for (int i = 0; i < BOARD_HEIGHT; i++)
        rows[i] = 0;

    for (int j = 0; j < BOARD_HEIGHT; j++)
    {
        int fill = 0;
        for (int k = 0; k < BOARD_WIDTH; k++)
        {
            if (field[j][k] == 1)
                fill++;
            else
                break;
        }
        if (fill == BOARD_WIDTH)
            rows[j] = 1;
    }
    return rows;
}