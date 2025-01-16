#ifndef UTILS_FIELD_H
#define UTILS_FIELD_H

#include "init.h"
#include <stdio.h>

void printField(int **field);
void fillField(Position *rodsH, int numH, Position *rodsV, int numV,
               int **field);

#endif
