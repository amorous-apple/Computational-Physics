#include "utils_field.h"

// Print out a field to visualize it
void printField(int **field) {
    for (int i = 0; i < SYSTEM_SIZE; i++) {
        for (int j = 0; j < SYSTEM_SIZE; j++) {
            printf("%d ", field[i][j]);
        }
        printf("\n");
    }
}

// Empties a field and then places all of the rods
void fillField(Position *rodsH, int numH, Position *rodsV, int numV,
               int **field) {
    for (int i = 0; i < SYSTEM_SIZE; i++) {
        for (int j = 0; j < SYSTEM_SIZE; j++) {
            field[i][j] = 0;
        }
    }

    for (int i = 0; i < numH; i++) {
        for (int j = 0; j < ROD_SIZE; j++) {
            field[SYSTEM_SIZE - 1 - rodsH[i].posY][rodsH[i].posX + j] = 1;
        }
    }
    for (int i = 0; i < numV; i++) {
        for (int j = 0; j < ROD_SIZE; j++) {
            field[SYSTEM_SIZE - 1 - rodsV[i].posY - j][rodsV[i].posX] = -1;
        }
    }
}
