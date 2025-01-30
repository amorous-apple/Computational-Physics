#include "int_velver.h"

// Calculating the velocity-verlet integrator to Collection2
void calc_velver(Particle* Collection1, Particle* Collection2) {
    Vector* Accel1 = calc_acc(Collection1);
    const double dt = params.timeStep;
    const double dt2 = dt * dt;

    // Update positions
    for (int i = 0; i < params.lineCount; i++) {
        Vector vel_term = vec_scalProd(dt, Collection1[i].vel);
        Vector accel_term = vec_scalProd(0.5 * dt2, Accel1[i]);
        Collection2[i].pos =
            vec_add(Collection1[i].pos, vec_add(vel_term, accel_term));
    }

    // Calculate new accelerations
    Vector* Accel2 = calc_acc(Collection2);

    // Update velocities
    for (int i = 0; i < params.lineCount; i++) {
        Vector avg_accel = vec_scalProd(0.5, vec_add(Accel1[i], Accel2[i]));
        Collection2[i].vel =
            vec_add(Collection1[i].vel, vec_scalProd(dt, avg_accel));
    }

    // Free allocated memory
    free(Accel1);
    free(Accel2);
}
