#include "int_hermite.h"

// Calculating the euler-cromer integrator to Collection2
void calc_hermite(Particle* Collection1, Particle* Collection2) {
    Vector* Accel = calc_acc(Collection1);

    for (int i = 0; i < params.lineCount; i++) {
        Collection2[i].vx = Collection1[i].vx + Accel[i].x * params.timeStep;
        Collection2[i].vy = Collection1[i].vy + Accel[i].y * params.timeStep;
        Collection2[i].vz = Collection1[i].vz + Accel[i].z * params.timeStep;

        Collection2[i].x =
            Collection1[i].x + Collection1[i].vx * params.timeStep;
        Collection2[i].y =
            Collection1[i].y + Collection1[i].vy * params.timeStep;
        Collection2[i].z =
            Collection1[i].z + Collection1[i].vz * params.timeStep;
    }

    free(Accel);
}
