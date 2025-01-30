#include "int_middle.h"

// Calculating the "Mittlungsmethode" by averaging velocities before calculating
// position
void calc_middle(Particle* Collection1, Particle* Collection2) {
    Vector* Accel = calc_acc(Collection1);
    const double dt = params.timeStep;

    for (int i = 0; i < params.lineCount; i++) {
        // Update velocity
        Collection2[i].vel =
            vec_add(Collection1[i].vel, vec_scalProd(dt, Accel[i]));

        // Calculate average velocity
        Vector avg_vel =
            vec_scalProd(0.5, vec_add(Collection1[i].vel, Collection2[i].vel));

        // Update position using the average velocity
        Collection2[i].pos =
            vec_add(Collection1[i].pos, vec_scalProd(dt, avg_vel));
    }

    free(Accel);
}
