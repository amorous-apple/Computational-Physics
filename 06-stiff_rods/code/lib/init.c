#include "init.h"

const int SYSTEM_SIZE = 64;
const int ROD_SIZE = 8;
const double ACTIVITY = 0.86;
const double ACTIVITY_INVERSE = 1.0 / ACTIVITY;

const unsigned long int NUM_STEPS = 1e6;
const int WRITE_INTERVAL = 10;
const int NUM_DATA_POINTS = (NUM_STEPS / WRITE_INTERVAL) + 1;

void init() {
    printf("System size: %d\n", SYSTEM_SIZE);
    printf("Activity: %lf\n", ACTIVITY);
}

int **init_occupancyField() {
    int **occupancyField = malloc(SYSTEM_SIZE * sizeof(int *));
    if (occupancyField == NULL) {
        perror("Error allocating memory for occupancyField\n");
        exit(EXIT_FAILURE);
    }
    int *intArr = malloc(SYSTEM_SIZE * SYSTEM_SIZE * sizeof(int));
    if (intArr == NULL) {
        perror("Error allocating memory for intArr\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < SYSTEM_SIZE; i++) {
        occupancyField[i] = intArr + (SYSTEM_SIZE * i);
    }

    return occupancyField;
}
