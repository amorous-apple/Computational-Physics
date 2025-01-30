#include "int_hermite_it.h"

// Iteration step
int ITERATION_STEPS = 2;

void hermite_iteration(Particle* Collection1, Particle* Collection2,
                       Vector* Accel, Vector* Jerk, Vector* Accel_p,
                       Vector* Jerk_p) {
    const double dt = params.timeStep;
    const double dt2 = dt * dt;

    // Calculate new predicted acceleration and jerk
    *Accel_p = *calc_acc(Collection2);  // predicted accel n+1
    *Jerk_p = *calc_jerk(Collection2);

    for (int i = 0; i < params.lineCount; i++) {
        // Velocity update
        Vector avg_accel = vec_scalProd(0.5, vec_add(Accel[i], Accel_p[i]));
        Vector jerk_diff =
            vec_scalProd(dt2 / 12.0, vec_sub(Jerk_p[i], Jerk[i]));
        Collection2[i].vel =
            vec_add(Collection1[i].vel,
                    vec_add(vec_scalProd(dt, avg_accel), jerk_diff));

        // Position update
        Vector avg_vel =
            vec_scalProd(0.5, vec_add(Collection2[i].vel, Collection1[i].vel));
        Vector accel_diff =
            vec_scalProd(dt2 / 12.0, vec_sub(Accel_p[i], Accel[i]));
        Collection2[i].pos = vec_add(
            Collection1[i].pos, vec_add(vec_scalProd(dt, avg_vel), accel_diff));
    }
}

// Calculate the Hermite integrator for Collection2
void calc_hermite_it(Particle* Collection1, Particle* Collection2) {
    Vector* Accel = calc_acc(Collection1);
    Vector* Jerk = calc_jerk(Collection1);
    const double dt = params.timeStep;
    const double dt2 = dt * dt;
    const double dt3 = dt2 * dt;

    // Prediction step
    for (int i = 0; i < params.lineCount; i++) {
        // Predict velocity
        Vector a_term = vec_scalProd(dt, Accel[i]);
        Vector j_term = vec_scalProd(0.5 * dt2, Jerk[i]);
        Collection2[i].vel =
            vec_add(Collection1[i].vel, vec_add(a_term, j_term));

        // Predict position
        Vector pos_term1 = vec_scalProd(dt, Collection1[i].vel);
        Vector pos_term2 = vec_scalProd(0.5 * dt2, Accel[i]);
        Vector pos_term3 = vec_scalProd(dt3 / 6.0, Jerk[i]);
        Collection2[i].pos =
            vec_add(Collection1[i].pos,
                    vec_add(vec_add(pos_term1, pos_term2), pos_term3));
    }

    // Allocate memory for predicted acceleration and jerk
    Vector* Accel_p = malloc(params.lineCount * sizeof(Vector));
    Vector* Jerk_p = malloc(params.lineCount * sizeof(Vector));

    // Iteration step
    for (int i = 0; i < ITERATION_STEPS; i++) {
        hermite_iteration(Collection1, Collection2, Accel, Jerk, Accel_p,
                          Jerk_p);
    }

    // Free allocated memory
    free(Accel);
    free(Jerk);
    free(Accel_p);
    free(Jerk_p);
}
