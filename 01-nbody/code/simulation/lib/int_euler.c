#include "int_euler.h"

Particle* calc_euler(Particle* Collection) {
    Particle* Collection2 = malloc(params.lineCount * sizeof(Particle));
    if (Collection == NULL) {
        perror("Error allocating memory for Collection2. \n");
        exit(EXIT_FAILURE);
    }

    Vector* Accel = calc_acc(Collection);

    for (int i = 0; i < params.lineCount; i++) {
        Collection2[i].x = Collection[i].vx * params.timeStep;
        Collection2[i].y = Collection[i].vy * params.timeStep;
        Collection2[i].z = Collection[i].vz * params.timeStep;

        Collection2[i].vx = Accel[i].x * params.timeStep;
        Collection2[i].vy = Accel[i].y * params.timeStep;
        Collection2[i].vz = Accel[i].z * params.timeStep;
    }
    return Collection2;
}
