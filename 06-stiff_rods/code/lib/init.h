#ifndef INIT_H
#define INIT_H

#include <stdio.h>
#include <stdlib.h>

extern const int SYSTEM_SIZE;
extern const int ROD_SIZE;
extern const double ACTIVITY;

extern const double BETA;
extern const double MU;

typedef struct {
    int posX;
    int posY;
} Position;

void init();

int **init_occupancyField();

#endif
