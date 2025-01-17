#include <stdio.h>
#include <time.h>

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

    rodsH[0].posX = 3;
    rodsH[0].posY = 1;
    rodsH[1].posX = 2;
    rodsH[1].posY = 4;
    numH = 2;

    rodsV[0].posX = 0;
    rodsV[0].posY = 3;
    rodsV[1].posX = 1;
    rodsV[1].posY = 2;
    numV = 2;

    int **occupancyField = init_occupancyField();
    // printField(occupancyField);

    printf("Rods: %d\n", numH + numV);
    fillField(rodsH, numH, rodsV, numV, occupancyField);
    printField(occupancyField);

    int startingRods = numH + numV;

    for (int i = 0; i < startingRods; i++) {
        delRod(rodsH, &numH, rodsV, &numV, occupancyField);
        printf("Rods: %d\n", numH + numV);
        printField(occupancyField);
    }

    free(rodsH);
    free(rodsV);
    free(occupancyField[0]);
    free(occupancyField);
}
