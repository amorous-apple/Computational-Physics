#include "int_euler.h"

void calc_euler(Particle* Collection1, Particle* Collection2) {
    // Particle* Collection2 = malloc(params.lineCount * sizeof(Particle));
    // if (Collection2 == NULL) {
    //     perror("Error allocating memory for Collection2. \n");
    //     exit(EXIT_FAILURE);
    // }

    Vector* Accel = calc_acc(Collection1);

    for (int i = 0; i < params.lineCount; i++) {
        // Collection2[i].mass = Collection1[i].mass;

        Collection2[i].x =
            Collection1[i].x + Collection1[i].vx * params.timeStep;
        Collection2[i].y =
            Collection1[i].y + Collection1[i].vy * params.timeStep;
        Collection2[i].z =
            Collection1[i].z + Collection1[i].vz * params.timeStep;

        Collection2[i].vx = Collection1[i].vx + Accel[i].x * params.timeStep;
        Collection2[i].vy = Collection1[i].vy + Accel[i].y * params.timeStep;
        Collection2[i].vz = Collection1[i].vz + Accel[i].z * params.timeStep;
    }

    free(Accel);
}
