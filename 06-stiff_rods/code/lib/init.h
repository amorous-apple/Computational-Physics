#ifndef INIT_H
#define INIT_H

#include <stdio.h>
#include <stdlib.h>

extern const int SYSTEM_SIZE;
extern const int ROD_SIZE;
extern const double ACTIVITY;
extern const double ACTIVITY_INVERSE;

extern const unsigned long int NUM_STEPS;
extern const int WRITE_INTERVAL;
extern const int NUM_DATA_POINTS;

typedef struct {
    int posX;
    int posY;
} Position;

void init();

int **init_occupancyField();

#endif
