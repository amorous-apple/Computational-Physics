#include <stdio.h>
#include <time.h>

#include "lib/functions.h"
#include "lib/init.h"
#include "lib/utils_data.h"
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

    int **occupancyField = init_occupancyField();
    // printField(occupancyField);

    fillField(rodsH, numH, rodsV, numV, occupancyField);
    // printField(occupancyField);

    unsigned long int **Data1 =
        malloc(NUM_DATA_POINTS * sizeof(unsigned long int *));
    unsigned long int *dataArr =
        malloc(4 * NUM_DATA_POINTS * sizeof(unsigned long int));
    if (Data1 == NULL || dataArr == NULL) {
        perror("Error allocating memory Data1 and dataArr!\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < NUM_DATA_POINTS; i++) {
        Data1[i] = dataArr + i * 4;
    }

    int numRods = numH + numV;
    Position posTemp;
    for (unsigned long int i = 0; i < NUM_STEPS; i++) {
        if (i % WRITE_INTERVAL == 0) {
            numRods = numH + numV;
            int index = i / WRITE_INTERVAL;
            printf("i = %ld\n", i - 1);
            // printField(occupancyField);
            Data1[index][0] = i;
            Data1[index][1] = numRods;
            Data1[index][2] = numH;
            Data1[index][3] = numV;
        }

        if (fiftyFifty() && randomBit(alphaIns(numRods))) {
            // Adding a stiff rod
            if (fiftyFifty()) {
                // Adding a horizontal rod
                posTemp.posX = randomCoord();
                posTemp.posY = randomCoord();
                // printf("Trying to add hRod at (%d, %d)\n", posTemp.posX,
                //        posTemp.posY);
                if (testRod(posTemp, 'h', occupancyField)) {
                    rodsH[numH] = posTemp;
                    placeRod(rodsH[numH], 'h', occupancyField);
                    numH++;
                } else {
                    // printf("Failed to add a rod\n");
                    continue;
                }
            } else {
                // Adding a vertical rod
                posTemp.posX = randomCoord();
                posTemp.posY = randomCoord();
                // printf("Trying to add vRod at (%d, %d)\n", posTemp.posX,
                //        posTemp.posY);
                if (testRod(posTemp, 'v', occupancyField)) {
                    rodsV[numV] = posTemp;
                    placeRod(rodsV[numV], 'v', occupancyField);
                    numV++;
                } else {
                    // printf("Failed to add a rod\n");
                    continue;
                }
            }
        } else {
            // Removing a stiff rod
            numRods = numH + numV;
            if (randomBit(alphaDel(numRods))) {
                // printf("Removing a rod\n");
                delRod(rodsH, &numH, rodsV, &numV, occupancyField);
            } else {
                // printf("Failed to remove a rod\n");
                continue;
            }
        }
        // if (i % WRITE_INTERVAL == 0) {
        //     numRods = numH + numV;
        //     int index = i / WRITE_INTERVAL;
        //     printf("i = %ld\n", i);
        //     printField(occupancyField);
        //     Data1[index][0] = i;
        //     Data1[index][1] = numRods;
        //     Data1[index][2] = numH;
        //     Data1[index][3] = numV;
        // }
    }
    data_write("plot1", Data1);

    free(rodsH);
    free(rodsV);
    free(occupancyField[0]);
    free(occupancyField);
}
