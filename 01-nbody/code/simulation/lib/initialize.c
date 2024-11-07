#include "initialize.h"

Particle* initialize(void) {
    FILE* pfile = fopen(params.filename, "r");
    if (ferror(pfile)) {
        perror("Error opening file. \n");
        exit(EXIT_FAILURE);
    }

    int n = params.lineCount;

    // Attempts to allocate necessary memory for all particles in the data
    Particle* Collection = malloc(n * sizeof(Particle));
    if (Collection == NULL) {
        perror("Error allocating memory for Collection. \n");
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

Particle* initialize2(void) {
    // Attempts to allocate necessary memory for all particles in the data
    Particle* Collection2 = malloc(params.lineCount * sizeof(Particle));
    if (Collection2 == NULL) {
        perror("Error allocating memory for Collection. \n");
        exit(EXIT_FAILURE);
    }
    return Collection2;
}
