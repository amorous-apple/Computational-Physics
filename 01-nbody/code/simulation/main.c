#include <stdio.h>

#include "lib/constants.h"
#include "lib/initialize.h"
#include "lib/int_euler.h"
#include "lib/utils.h"
#include "utils.h"

Parameters params;

int main(int argc, char* argv[]) {
    // Defining time variables for measuring CPU time elapsed
    clock_t start, end;
    double secUsed;
    start = clock();

    def_params(argc, argv);
    // Initializaing a collection of data from the file
    Particle* Collection1 = initialize();
    // Initializing an empty collection
    Particle* Collection2 = initialize2();

    // printf("Test\n");
    // printf("Filename: %s\n", params.filename);
    // printf("Fileout: %s\n", params.fileout);

    remove(params.fileout);
    FILE* fileout = openFileout();

    for (int i = 0; i <= params.stepCount; i++) {
        double timeCurrent = 0.0 + i * params.timeStep;

        for (int j = 0; j < params.lineCount; j++) {
            char dataLine[params.MAX_LINE_LENGTH];
            snprintf(dataLine, params.MAX_LINE_LENGTH,
                     "%.8lf,%.8lf,%.8lf,%.8lf,%.8lf, %.8lf, %.8lf\n",
                     timeCurrent, Collection1[j].x, Collection1[j].y,
                     Collection1[j].z, Collection1[j].vz, Collection1[j].vy,
                     Collection1[j].vz);
            fprintf(fileout, "%s", dataLine);
        }
        fprintf(fileout, "\n");

        Collection2 = Collection1;
        Collection1 = calc_euler(Collection2);
    }

    // Ending and printing time measurement to console
    end = clock();
    secUsed = calc_secUsed(start, end);
    printf("Program took: %f seconds \n", secUsed);
}
