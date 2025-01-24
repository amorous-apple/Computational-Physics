#include "int_hermite_it.h"
//iteration step
int ITERATION_STEPS = 2;    // I tried to allocate Jerk_p once and pass space as a function parameter.
                            // Let me know what you think.
void hermite_iteration(Particle* Collection1, Particle* Collection2, Vector* Accel,  Vector* Jerk, Vector* Accel_p,  Vector* Jerk_p) {
    
        // Calculating new predicted acceleration and jerk
    *Accel_p = *calc_acc(Collection2);  // predicted accel n+1
    *Jerk_p = *calc_jerk(Collection2);

    for (int i = 0; i < params.lineCount; i++) {
        
        Collection2[i].vx =
            Collection1[i].vx + (Accel[i].x + Accel_p[i].x)/2.0 * params.timeStep +
            (Jerk_p[i].x - Jerk[i].x) / 12.0 * params.timeStep *
                params.timeStep;
        Collection2[i].vy =
            Collection1[i].vy + (Accel[i].y + Accel_p[i].y)/2.0 * params.timeStep +
            (Jerk_p[i].y - Jerk[i].y) / 12.0 * params.timeStep *
                params.timeStep;
        Collection2[i].vz =
            Collection1[i].vz + (Accel[i].z + Accel_p[i].z)/2.0 * params.timeStep +
            (Jerk_p[i].z - Jerk[i].z) / 12.0 * params.timeStep *
                params.timeStep;

        Collection2[i].x =
            Collection1[i].x + (Collection2[i].vx + Collection1[i].vx)/2.0 * params.timeStep +
            (Accel_p[i].x - Accel[i].x) / 12.0 * params.timeStep *
                params.timeStep;
        Collection2[i].y =
            Collection1[i].y + (Collection2[i].vy + Collection1[i].vy)/2.0 * params.timeStep +
            (Accel_p[i].y - Accel[i].y) / 12.0 * params.timeStep *
                params.timeStep;
        Collection2[i].z =
            Collection1[i].z + (Collection2[i].vz + Collection1[i].vz)/2.0 * params.timeStep +
            (Accel_p[i].z - Accel[i].z) / 12.0 * params.timeStep *
                params.timeStep;
    
    }

}

// Calculating the hermite integrator to Collection2
void calc_hermite_it(Particle* Collection1, Particle* Collection2) {
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
    Vector* Accel_p = malloc(params.lineCount * sizeof(Vector));  // predicted accel n+1
    Vector* Jerk_p = malloc(params.lineCount * sizeof(Vector));

    for (int i = 0; i < ITERATION_STEPS; i++) {
        hermite_iteration(Collection1, Collection2, Accel, Jerk, Accel_p, Jerk_p);
    }
    

    // TODO: Allocating and freeing this amount of memory with data for every
    // particle is a poor use of resources -> Allocate once and pass space as a
    // function parameter
    free(Accel);
    free(Jerk);
    free(Accel_p);
    free(Jerk_p);
}
