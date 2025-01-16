#ifndef INIT_H
#define INIT_H

#include <stdio.h>
#include <stdlib.h>

extern const int SYSTEM_SIZE;
extern const int ROD_SIZE;
extern const double ACTIVITY;

typedef struct {
    int posX;
    int posY;
} Position;

void init();

int **init_occupancyField();

#endif
