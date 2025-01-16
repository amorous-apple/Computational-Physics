#include <stdio.h>

#include "lib/init.h"
#include "lib/utils_field.h"
#include "stdlib.h"

int main() {
    init();

    int MAX_RODS = (SYSTEM_SIZE * SYSTEM_SIZE / ROD_SIZE) + 1;

    Position *rodsH = malloc(MAX_RODS * sizeof(Position));
    Position *rodsV = malloc(MAX_RODS * sizeof(Position));

    int numH = 0;
    int numV = 0;

    int countTotal = numH + numV;

    rodsH[0].posX = 0;
    rodsH[0].posY = 0;
    numH = 1;

    rodsV[0].posX = 4;
    rodsV[0].posX = 4;
    numV = 1;

    int **occupancyField = init_occupancyField();
    printField(occupancyField);

    printf("Initial field\n");
    fillField(rodsH, numH, rodsV, numV, occupancyField);
    printField(occupancyField);
}
