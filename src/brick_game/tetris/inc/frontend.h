#ifndef FRONTEND_H
#define FRONTEND_H

#include "define.h"

void printRectangle(int top, int bottom, int right, int left);
void printField(int **field);
void printNextField(int **field);
void eraseNextField();
void printOverlay(void);

#endif