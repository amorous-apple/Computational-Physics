#include "initialize.h"

Particle* initialize(void) {
    FILE* psrcfile = fopen(params.filename, "r");
    if (ferror(psrcfile)) {
        perror("Error opening file. \n");
        exit(EXIT_FAILURE);
    }

    // Attempts to allocate necessary memory for all particles in the data
    Particle* Collection = malloc(params.lineCount * sizeof(Particle));
    if (Collection == NULL) {
        perror("Error allocating memory for Collection1. \n");
        exit(EXIT_FAILURE);
    }

    // Reading and storing the data for the bodies in Collection
    data_read(Collection, psrcfile);

    fclose(psrcfile);
    return Collection;
}

Particle* initialize2(void) {
    // Attempting to allocate necessary memory for all particles in the data
    Particle* Collection2 = malloc(params.lineCount * sizeof(Particle));
    if (Collection2 == NULL) {
        perror("Error allocating memory for Collection2. \n");
        exit(EXIT_FAILURE);
    }
    return Collection2;
}
