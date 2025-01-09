#include "calc_ener.h"

double calc_ener(Particle* Collection) {
    double total_ener = 0.0;

    for (int i = 0; i < params.lineCount; i++) {
        // Calculating and adding the kinetic energy components for particle i
        total_ener += (1.0 / 2.0) * Collection[i].mass *
                      (pow(Collection[i].vx, 2) + pow(Collection[i].vx, 2) +
                       pow(Collection[i].vx, 2));

// Calculating and adding the gravitational potential
// energy for every particle
#pragma omp parallel for
        for (int i = 0; i < params.lineCount; i++) {
            for (int j = 0; j < params.lineCount; j++) {
                // Preventing an object form calculating the potential on itself
                if (j == i) {
                    continue;
                }

                Vector pos1;
                pos1.x = Collection[i].x;
                pos1.y = Collection[i].y;
                pos1.z = Collection[i].z;

                Vector pos2;
                pos2.x = Collection[i].x;
                pos2.y = Collection[i].y;
                pos2.z = Collection[i].z;

                double separation = vec_sepDist(pos1, pos2);
                if (separation < 1E-6) {
                    continue;
                } else {
                    double inv_separation = 1.0 / vec_sepDist(pos1, pos2);
                    total_ener += (Collection[i].mass * Collection[j].mass) *
                                  inv_separation;
                }
            }
        }
    }
    return total_ener;
}
