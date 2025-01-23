#include "utils_field.h"

// Print out a field to visualize it
void printField(int **field) {
    for (int i = 0; i < SYSTEM_SIZE; i++) {
        for (int j = 0; j < SYSTEM_SIZE; j++) {
            switch (field[i][j]) {
                case 0:
                    printf(". ");
                    break;
                case 1:
                    printf("< ");
                    break;
                case 2:
                    printf("─ ");
                    break;
                case 3:
                    printf("> ");
                    break;
                case -1:
                    printf("v ");
                    break;
                case -2:
                    printf("| ");
                    break;
                case -3:
                    printf("^ ");
                    break;
            }
        }
        printf("\n");
    }
}

// Testing if a rod can be inserted into a dataset without overlap (1 if
// insertable, 0 otherwise)
int testRod(Position rodPosition, char rodType, int **field) {
    if (rodType == 'h') {
        int mVal = SYSTEM_SIZE - 1 - rodPosition.posY;
        int nVal = rodPosition.posX;
        for (int i = 0; i < ROD_SIZE; i++) {
            // Periodic boundary conditions
            if (nVal > SYSTEM_SIZE - 1) {
                nVal -= SYSTEM_SIZE;
            }
            if (field[mVal][nVal] != 0) {
                return 0;
            }
            nVal++;
        }
        return 1;
    } else if (rodType == 'v') {
        int nVal = rodPosition.posX;
        int mVal = SYSTEM_SIZE - 1 - rodPosition.posY;
        for (int i = 0; i < ROD_SIZE; i++) {
            // Periodic boundary conditions
            if (mVal < 0) {
                mVal += SYSTEM_SIZE;
            }
            if (field[mVal][nVal] != 0) {
                return 0;
            }
            mVal--;
        }
        return 1;
    } else {
        printf("Invalid rodType of %c\n!", rodType);
        exit(EXIT_FAILURE);
    }
}

// Placing a single rod into a field (returns 1 if placed and 0 otherwise)
int placeRod(Position rodPosition, char rodType, int **field) {
    if (!testRod(rodPosition, rodType, field)) {
        printf("Invalid %c rod placement at (%d,%d)\n", rodType,
               rodPosition.posX, rodPosition.posY);
        return 0;
    }
    if (rodType == 'h') {
        int nVal = rodPosition.posX;
        int mVal = SYSTEM_SIZE - 1 - rodPosition.posY;
        field[mVal][nVal] = 1;
        nVal++;
        for (int j = 1; j < ROD_SIZE - 1; j++) {
            field[mVal][nVal] = 2;
            nVal++;
            if (nVal > SYSTEM_SIZE - 1) {
                nVal -= SYSTEM_SIZE;
            }
            // Periodic boundary conditions
            if (nVal > SYSTEM_SIZE - 1) {
                nVal -= SYSTEM_SIZE;
            }
        }
        field[mVal][nVal] = 3;
        return 1;
    } else if (rodType == 'v') {
        int nVal = rodPosition.posX;
        int mVal = SYSTEM_SIZE - 1 - rodPosition.posY;
        field[mVal][nVal] = -1;
        mVal--;
        if (mVal < 0) {
            mVal += SYSTEM_SIZE;
        }
        for (int j = 1; j < ROD_SIZE - 1; j++) {
            field[mVal][nVal] = -2;
            mVal--;
            // Periodic boundary conditions
            if (mVal < 0) {
                mVal += SYSTEM_SIZE;
            }
        }
        field[mVal][nVal] = -3;
        return 1;
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

// Deleting a random rod from the field
int **delRod(Position *rodsH, int *numH, Position *rodsV, int *numV,
             int **field) {
    int numRods = *numH + *numV;
    int randID = (rand() % numRods);
    // printf("randID: %d\n", randID);

    if (randID <= *numH - 1) {
        for (int i = randID; i < *numH - 1; i++) {
            rodsH[i] = rodsH[i + 1];
        }
        (*numH)--;
    } else {
        randID -= *numH;
        for (int i = randID; i < *numV - 1; i++) {
            rodsV[i] = rodsV[i + 1];
        }
        (*numV)--;
    }

    fillField(rodsH, *numH, rodsV, *numV, field);

    return field;
}
