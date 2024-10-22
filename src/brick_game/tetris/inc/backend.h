#ifndef BACKEND_H
#define BACKEND_H

#include "objects.h"

void initShapePosition(Shape_t *shape);
Shape_t createShape();
void addShapeToField(Shape_t *shape, int **field);
void eraseShapeFromField(Shape_t *shape, int **field);
int generateInt(int limit);
bool checkTouch(Shape_t *shape, int **field, int action);

bool contains(Shape_t *result, Coor_t cell);
Cells_t initCells();
void getExtremeCells(Cells_t *extremeCells, Shape_t *shape, int action);
bool checkNonEmpty(Cells_t *extremeCells, int **field, int action);

Coor_t getRotatedCoords(Shape_t *shape, int i);
int getPixelsToDown(Cells_t *extremeCells, int **field);
int *getFilledRows(int **field);

int **initMatrix(int row, int col);
void removeMatrix(int **matrix, int row);

void shapeToMarix(Shape_t *shape, int **field);

#endif