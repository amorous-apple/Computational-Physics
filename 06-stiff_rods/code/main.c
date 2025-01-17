#include <stdio.h>
#include <time.h>

#include "lib/functions.h"
#include "lib/init.h"
#include "lib/utils_field.h"
#include "stdlib.h"

int main() {
    // init();

    srand(time(NULL));  // sets random seed

    int MAX_RODS = (SYSTEM_SIZE * SYSTEM_SIZE / ROD_SIZE) + 1;

    Position *rodsH = malloc(MAX_RODS * sizeof(Position));
    if (rodsH == NULL) {
        perror("Error allocating memory for rodsH\n");
        exit(EXIT_FAILURE);
    }
    Position *rodsV = malloc(MAX_RODS * sizeof(Position));
    if (rodsV == NULL) {
        perror("Error allocating memory for rodsV\n");
        exit(EXIT_FAILURE);
    }

    int numH = 0;
    int numV = 0;

    // int countTotal = numH + numV;

    // rodsH[0].posX = 0;
    // rodsH[0].posY = 3;
    // rodsH[1].posX = 0;
    // rodsH[1].posY = 4;
    // rodsH[2].posX = 0;
    // rodsH[2].posY = 2;
    // rodsH[3].posX = 0;
    // rodsH[3].posY = 3;
    numH = 0;

    // rodsV[0].posX = 0;
    // rodsV[0].posY = 0;
    // rodsV[1].posX = 1;
    // rodsV[1].posY = 0;
    // rodsV[2].posX = 2;
    // rodsV[2].posY = 0;
    // rodsV[3].posX = 3;
    // rodsV[3].posY = 0;
    numV = 0;

    int **occupancyField = init_occupancyField();
    // printField(occupancyField);

    printf("Rods: %d\n", numH + numV);
    fillField(rodsH, numH, rodsV, numV, occupancyField);
    printField(occupancyField);

    // int startingRods = numH + numV;
    //
    // for (int i = 0; i < startingRods - 1; i++) {
    //     delRod(rodsH, &numH, rodsV, &numV, occupancyField);
    //     printf("Rods: %d\n", numH + numV);
    //     printField(occupancyField);
    // }

    int numRods = numH + numV;
    Position posTemp;
    for (int i = 0; i < 10000; i++) {
        if (fiftyFifty()) {
            // Adding a stiff rod
            if (fiftyFifty()) {
                // Adding a horizontal rod
                posTemp.posX = randomCoord();
                posTemp.posY = randomCoord();
                printf("Trying to add hRod at (%d, %d)\n", posTemp.posX,
                       posTemp.posY);
                if (testRod(posTemp, 'h', occupancyField)) {
                    rodsH[numH] = posTemp;
                    placeRod(rodsH[numH], 'h', occupancyField);
                    numH++;
                } else {
                    printf("Failed to add a rod\n");
                    continue;
                }
            } else {
                // Adding a vertical rod
                posTemp.posX = randomCoord();
                posTemp.posY = randomCoord();
                printf("Trying to add vRod at (%d, %d)\n", posTemp.posX,
                       posTemp.posY);
                if (testRod(posTemp, 'v', occupancyField)) {
                    rodsV[numV] = posTemp;
                    placeRod(rodsV[numV], 'v', occupancyField);
                    numV++;
                } else {
                    printf("Failed to add a rod\n");
                    continue;
                }
            }
        } else {
            // Removing a stiff rod
            numRods = numH + numV;
            if (randomBit(alphaDel(numRods))) {
                printf("Removing a rod\n");
                delRod(rodsH, &numH, rodsV, &numV, occupancyField);
            } else {
                printf("Failed to remove a rod\n");
                continue;
            }
        }
        printf("i = %i\n", i);
        printField(occupancyField);
    }

    free(rodsH);
    free(rodsV);
    free(occupancyField[0]);
    free(occupancyField);
}
