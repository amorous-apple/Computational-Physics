#include "initialize.h"

#include <stdio.h>
#include <stdlib.h>

#include "constants.h"

Particle* initialize(int argc, char* argv[]) {
    Parameters params = def_params(argc, argv);
    FILE* pfile = fopen(params.filename, "r");
    if (ferror(pfile)) {
        printf("Error opening file. \n");
        exit(EXIT_FAILURE);
    }

    int n = params.lineCount;

    // Attempts to allocate necessary memory for all particles in the data
    Particle* Collection = malloc(n * sizeof(Particle));
    if (!Collection) {
        printf("Error allocating memory for Collection. \n");
        exit(EXIT_FAILURE);
    }

    // Reading and storing the data for the bodies in Collection
    for (int i = 0; i < n; i++) {
        if (fscanf(pfile, "%lf,%lf,%lf,%lf,%lf,%lf,%lf", &Collection[i].x,
                   &Collection[i].y, &Collection[i].z, &Collection[i].vx,
                   &Collection[i].vy, &Collection[i].vz,
                   &Collection[i].mass) != 7) {
            printf("Error reading data for body %i \n", i);
            free(Collection);
            fclose(pfile);
            exit(EXIT_FAILURE);
        }
    }

    fclose(pfile);
    return Collection;
}
