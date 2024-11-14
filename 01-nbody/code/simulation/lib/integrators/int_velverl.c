#include "int_velverl.h"

// Calculating the velocity-verlet integrator to Collection2
void calc_velverl(Particle* Collection1, Particle* Collection2) {
    Vector* Accel1 = calc_acc(Collection1);

    for (int i = 0; i < params.lineCount; i++) {
        Collection2[i].x = Collection1[i].x +
                           Collection1[i].vx * params.timeStep +
                           (1.0 / 2.0) * Accel1[i].x * pow(params.timeStep, 2);
        Collection2[i].y = Collection1[i].y +
                           Collection1[i].vy * params.timeStep +
                           (1.0 / 2.0) * Accel1[i].y * pow(params.timeStep, 2);
        Collection2[i].z = Collection1[i].z +
                           Collection1[i].vz * params.timeStep +
                           (1.0 / 2.0) * Accel1[i].z * pow(params.timeStep, 2);
    }
    Vector* Accel2 = calc_acc(Collection2);

    for (int i = 0; i < params.lineCount; i++) {
        Collection2[i].vx =
            Collection1[i].vx +
            (1.0 / 2.0) * (Accel1[i].x + Accel2[i].x) * params.timeStep;
        Collection2[i].vy =
            Collection1[i].vy +
            (1.0 / 2.0) * (Accel1[i].y + Accel2[i].y) * params.timeStep;
        Collection2[i].vz =
            Collection1[i].vz +
            (1.0 / 2.0) * (Accel1[i].z + Accel2[i].z) * params.timeStep;
    }

    free(Accel1);
    free(Accel2);
}
