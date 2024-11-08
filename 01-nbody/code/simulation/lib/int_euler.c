#include "int_euler.h"

void calc_euler(Particle* Collection1) {
    Vector* Accel = calc_acc(Collection1);

    // #pragma omp parallel for
    for (int i = 0; i < params.lineCount; i++) {
        Collection1[i].x += Collection1[i].vx * params.timeStep;
        Collection1[i].y += Collection1[i].vy * params.timeStep;
        Collection1[i].y += Collection1[i].vz * params.timeStep;

        Collection1[i].vx += Accel[i].x * params.timeStep;
        Collection1[i].vy += Accel[i].y * params.timeStep;
        Collection1[i].vz += Accel[i].z * params.timeStep;
    }

    free(Accel);
}
