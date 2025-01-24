#include "int_hermite.h"

// Calculating the hermite integrator to Collection2
void calc_hermite(Particle* Collection1, Particle* Collection2) {
    Vector* Accel = calc_acc(Collection1);
    Vector* Jerk = calc_jerk(Collection1);
    
    for (int i = 0; i < params.lineCount; i++) {
        // Calculating the predicted velocity
        Collection2[i].vx = Collection1[i].vx + Accel[i].x * params.timeStep +
                           1.0 / 2 * Jerk[i].x * pow(params.timeStep, 2);
        Collection2[i].vy = Collection1[i].vy + Accel[i].y * params.timeStep +
                           1.0 / 2 * Jerk[i].y * pow(params.timeStep, 2);
        Collection2[i].vz = Collection1[i].vz + Accel[i].z * params.timeStep +
                           1.0 / 2 * Jerk[i].z * pow(params.timeStep, 2);

        // Calculating the predicted position
        Collection2[i].x = Collection1[i].x +
                          Collection1[i].vx * params.timeStep +
                          1.0 / 2 * Accel[i].x * pow(params.timeStep, 2) +
                          1.0 / 6 * Jerk[i].x * pow(params.timeStep, 3);
        Collection2[i].y = Collection1[i].y +
                          Collection1[i].vy * params.timeStep +
                          1.0 / 2 * Accel[i].y * pow(params.timeStep, 2) +
                          1.0 / 6 * Jerk[i].y * pow(params.timeStep, 3);
        Collection2[i].z = Collection1[i].z +
                          Collection1[i].vz * params.timeStep +
                          1.0 / 2 * Accel[i].z * pow(params.timeStep, 2) +
                          1.0 / 6 * Jerk[i].z * pow(params.timeStep, 3);
    }
    // Calculating new predicted acceleration and jerk
    Vector* Accel_p = calc_acc(Collection2);  // predicted accel n+1
    Vector* Jerk_p = calc_jerk(Collection2);

    // Vector* Accel_next = malloc(params.lineCount * sizeof(Vector)); //a_n+1
    // Vector* Jerk_next = malloc(params.lineCount * sizeof(Vector));
    // calculate the
    for (int i = 0; i < params.lineCount; i++) {
        // TODO: You're allowed to delete code - it will be in the git history
        // anyway in case we need it later
        //
        // Accel_next[i].x = Accel[i].x +
        // Jerk[i].x * params.timeStep - 3 * (Accel[i].x - Accel_p[i].x) - (2 *
        // Jerk[i].x + Jerk_p[i].x) * params.timeStep +
        //     2 * (Accel[i].x - Accel_p[i].x) + (Jerk[i].x + Jerk_p[i].x) *
        //     params.timeStep;
        // Accel_next[i].y = Accel[i].y + Jerk[i].y * params.timeStep - 3 *
        // (Accel[i].y - Accel_p[i].y) - (2 * Jerk[i].y + Jerk_p[i].y) *
        // params.timeStep +
        //     2 * (Accel[i].y - Accel_p[i].y) + (Jerk[i].y + Jerk_p[i].y) *
        //     params.timeStep;
        // Accel_next[i].z = Accel[i].z + Jerk[i].z * params.timeStep - 3 *
        // (Accel[i].z - Accel_p[i].z) - (2 * Jerk[i].z + Jerk_p[i].z) *
        // params.timeStep +
        //     2 * (Accel[i].z - Accel_p[i].z) + (Jerk[i].z + Jerk_p[i].z) *
        //     params.timeStep;

        // Jerk_next[i].x = Jerk[i].x - 6 * (Accel[i].x - Accel_p[i].x) *
        // (1/params.timeStep) - 2 * (2 * Jerk[i].x + Jerk_p[i].x) + 6 *
        // (Accel[i].x - Accel_p[i].x) * (1/params.timeStep) + 3 * (Jerk[i].x +
        // Jerk_p[i].x); Jerk_next[i].y = Jerk[i].y - 6 * (Accel[i].y -
        // Accel_p[i].y) * (1/params.timeStep) - 2 * (2 * Jerk[i].y +
        // Jerk_p[i].y) + 6 * (Accel[i].y - Accel_p[i].y) * (1/params.timeStep)
        // + 3 * (Jerk[i].y + Jerk_p[i].y); Jerk_next[i].z = Jerk[i].z - 6 *
        // (Accel[i].z - Accel_p[i].z) * (1/params.timeStep) - 2 * (2 *
        // Jerk[i].z + Jerk_p[i].z) + 6 * (Accel[i].z - Accel_p[i].z) *
        // (1/params.timeStep) + 3 * (Jerk[i].z + Jerk_p[i].z);

    
        Collection2[i].vx =
            Collection2[i].vx - (Accel[i].x - Accel_p[i].x) * params.timeStep -
            (2 * Jerk[i].x + Jerk_p[i].x) / 3 * params.timeStep *
                params.timeStep +
            1.0 / 4 *
                (2 * (Accel[i].x - Accel_p[i].x) * params.timeStep +
                 (Jerk[i].x + Jerk_p[i].x) * params.timeStep * params.timeStep);
        Collection2[i].vy =
            Collection2[i].vy - (Accel[i].y - Accel_p[i].y) * params.timeStep -
            (2 * Jerk[i].y + Jerk_p[i].y) / 3 * params.timeStep *
                params.timeStep +
            1.0 / 4 *
                (2 * (Accel[i].y - Accel_p[i].y) * params.timeStep +
                 (Jerk[i].y + Jerk_p[i].y) * params.timeStep * params.timeStep);
        Collection2[i].vz =
            Collection2[i].vz - (Accel[i].z - Accel_p[i].z) * params.timeStep -
            (2 * Jerk[i].z + Jerk_p[i].z) / 3 * params.timeStep *
                params.timeStep +
            1.0 / 4 *
                (2 * (Accel[i].z - Accel_p[i].z) * params.timeStep +
                 (Jerk[i].z + Jerk_p[i].z) * params.timeStep * params.timeStep);

        Collection2[i].x = Collection2[i].x -
                           (Accel[i].x - Accel_p[i].x) / 4 * params.timeStep *
                               params.timeStep -
                           (2 * Jerk[i].x + Jerk_p[i].x) / 12 *
                               params.timeStep * params.timeStep *
                               params.timeStep +
                           1.0 / 20 *
                               (2 * (Accel[i].x - Accel_p[i].x) *
                                    params.timeStep * params.timeStep +
                                (Jerk[i].x + Jerk_p[i].x) * params.timeStep *
                                    params.timeStep * params.timeStep);
        Collection2[i].y = Collection2[i].y -
                           (Accel[i].y - Accel_p[i].y) / 4 * params.timeStep *
                               params.timeStep -
                           (2 * Jerk[i].y + Jerk_p[i].y) / 12 *
                               params.timeStep * params.timeStep *
                               params.timeStep +
                           1.0 / 20 *
                               (2 * (Accel[i].y - Accel_p[i].y) *
                                    params.timeStep * params.timeStep +
                                (Jerk[i].y + Jerk_p[i].y) * params.timeStep *
                                    params.timeStep * params.timeStep);
        Collection2[i].z = Collection2[i].z -
                           (Accel[i].z - Accel_p[i].z) / 4 * params.timeStep *
                               params.timeStep -
                           (2 * Jerk[i].z + Jerk_p[i].z) / 12 *
                               params.timeStep * params.timeStep *
                               params.timeStep +
                           1.0 / 20 *
                               (2 * (Accel[i].z - Accel_p[i].z) *
                                    params.timeStep * params.timeStep +
                                (Jerk[i].z + Jerk_p[i].z) * params.timeStep *
                                    params.timeStep * params.timeStep);
    }

    // TODO: Allocating and freeing this amount of memory with data for every
    // particle is a poor use of resources -> Allocate once and pass space as a
    // function parameter
    free(Accel);
    free(Jerk);
    free(Accel_p);
    free(Jerk_p);
    //free(Prediction);
}
