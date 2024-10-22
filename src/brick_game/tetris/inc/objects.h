#ifndef OBJECTS_H
#define OBJECTS_H

#include <ncurses.h>
#include "define.h"

typedef struct
{
    int x;
    int y;
} Coor_t;

typedef struct
{
    int size;
    int center;
    Coor_t blocks[4];
} Shape_t;

typedef struct
{
    Coor_t blocks[4];
} Cells_t;

#define I_SHAPE         \
    {                   \
        4,              \
            3,          \
            .blocks = { \
                {0, 0}, \
                {0, 1}, \
                {0, 2}, \
                {0, 3}  \
            }           \
    }

#define J_SHAPE         \
    {                   \
        3,              \
            3,          \
            .blocks = { \
                {1, 0}, \
                {0, 0}, \
                {0, 1}, \
                {0, 2}, \
            }           \
    }
#define O_SHAPE         \
    {                   \
        2,              \
            0,          \
            .blocks = { \
                {0, 0}, \
                {0, 1}, \
                {1, 1}, \
                {1, 0}, \
            }           \
    }
#define S_SHAPE         \
    {                   \
        3,              \
            2,          \
            .blocks = { \
                {0, 0}, \
                {0, 1}, \
                {1, 1}, \
                {1, 2}, \
            }           \
    }
#define Z_SHAPE         \
    {                   \
        3,              \
            2,          \
            .blocks = { \
                {1, 0}, \
                {1, 1}, \
                {0, 1}, \
                {0, 2}, \
            }           \
    }
#define T_SHAPE         \
    {                   \
        3,              \
            2,          \
            .blocks = { \
                {0, 0}, \
                {0, 1}, \
                {0, 2}, \
                {1, 1}, \
            }           \
    }
#define L_SHAPE         \
    {                   \
        3,              \
            3,          \
            .blocks = { \
                {0, 0}, \
                {0, 1}, \
                {0, 2}, \
                {1, 2}, \
            }           \
    }

#endif