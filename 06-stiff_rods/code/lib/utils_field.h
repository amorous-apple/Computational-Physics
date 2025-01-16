#ifndef UTILS_FIELD_H
#define UTILS_FIELD_H

#include "init.h"
#include <stdio.h>
#include <stdlib.h>

void printField(int **field);
int testRod(Position rodPosition, char rodType, int **field);
void placeRod(Position rodPosition, char rodType, int **field);
void fillField(Position *rodsH, int numH, Position *rodsV, int numV,
               int **field);

#endif
