#include "init.h"

const int SYSTEM_SIZE = 64;
const int ROD_SIZE = 8;
const double ACTIVITY = 1.1;
const double ACTIVITY_INVERSE = 1.0 / ACTIVITY;

const double BETA = 5.0;
const double MU = 1.0;

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
