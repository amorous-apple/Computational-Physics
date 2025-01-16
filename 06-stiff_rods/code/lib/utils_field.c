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

// Testing if a rod can be inserted into a dataset without overlap
int testRod(Position rodPosition, char rodType, int **field) {
    if (rodType == 'h') {
        for (int i = 0; i < ROD_SIZE; i++) {
            int nVal = rodPosition.posX + i;
            if (nVal > SYSTEM_SIZE - 1) {
                nVal -= SYSTEM_SIZE;
            }
            int mVal = SYSTEM_SIZE - 1 - rodPosition.posY;
            if (field[mVal][nVal] != 0) {
                return 0;
            }
        }
        return 1;
    } else if (rodType == 'v') {
        for (int i = 0; i < ROD_SIZE; i++) {
            int nVal = rodPosition.posX;
            int mVal = SYSTEM_SIZE - 1 - rodPosition.posY - i;
            if (mVal < 0) {
                mVal += SYSTEM_SIZE;
            }
            if (field[mVal][nVal] != 0) {
                return 0;
            }
        }
        return 1;
    } else {
        printf("Invalid rodType of %c\n!", rodType);
        exit(EXIT_FAILURE);
    }
}

// Placing a single rod into a field
void placeRod(Position rodPosition, char rodType, int **field) {
    if (!testRod(rodPosition, rodType, field)) {
        printf("Invalid %c rod placement at (%d,%d)\n", rodType,
               rodPosition.posX, rodPosition.posY);
        exit(EXIT_FAILURE);
    }
    if (rodType == 'h') {
        for (int j = 0; j < ROD_SIZE; j++) {
            int nVal = rodPosition.posX + j;
            if (nVal > SYSTEM_SIZE - 1) {
                nVal -= SYSTEM_SIZE;
            }
            int mVal = SYSTEM_SIZE - 1 - rodPosition.posY;
            field[mVal][nVal] = 1;
        }
    } else if (rodType == 'v') {
        for (int j = 0; j < ROD_SIZE; j++) {
            int nVal = rodPosition.posX;
            int mVal = SYSTEM_SIZE - 1 - rodPosition.posY - j;
            if (mVal < 0) {
                mVal += SYSTEM_SIZE;
            }
            field[mVal][nVal] = -1;
        }
    } else {
        printf("Invalid rodType of %c\n!", rodType);
        exit(EXIT_FAILURE);
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
        placeRod(rodsH[i], 'h', field);
    }
    for (int i = 0; i < numV; i++) {
        placeRod(rodsV[i], 'v', field);
    }
}
