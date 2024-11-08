#include "int_middle.h"

// Calculating the "Mittlungsmethode" by averaging velocities before calculating
// position
void calc_middle(Particle* Collection1, Particle* Collection2) {
    Vector* Accel = calc_acc(Collection1);

    for (int i = 0; i < params.lineCount; i++) {
        Collection2[i].vx = Collection1[i].vx + Accel[i].x * params.timeStep;
        Collection2[i].vy = Collection1[i].vy + Accel[i].y * params.timeStep;
        Collection2[i].vz = Collection1[i].vz + Accel[i].z * params.timeStep;

        Collection2[i].x =
            Collection1[i].x + (1.0 / 2.0) *
                                   (Collection1[i].vx + Collection2[i].vx) *
                                   params.timeStep;
        Collection2[i].y =
            Collection1[i].y + (1.0 / 2.0) *
                                   (Collection1[i].vy + Collection2[i].vy) *
                                   params.timeStep;
        Collection2[i].z =
            Collection1[i].z + (1.0 / 2.0) *
                                   (Collection1[i].vz + Collection2[i].vz) *
                                   params.timeStep;
    }

    free(Accel);
}
