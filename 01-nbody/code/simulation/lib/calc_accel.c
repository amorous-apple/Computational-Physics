#include "calc_accel.h"

Vector* calc_force(Particle* Collection) {
    Vector* Force = malloc(params.lineCount * sizeof(Vector));
    if (Force == NULL) {
        perror("Error allocating memory for Force!");
        exit(EXIT_FAILURE);
    }
    int n = params.lineCount;

    for (int i = 0; i < n; i++) {
        Vector force_total;
        force_total.x = 0;
        force_total.y = 0;
        force_total.z = 0;

        Vector pos1;
        pos1.x = Collection[i].x;
        pos1.y = Collection[i].y;
        pos1.z = Collection[i].z;

        for (int j = 0; j < n; j++) {
            // Preventing an object form calculating the force on itself
            if (j == i) {
                continue;
            }

            Vector pos2;
            pos2.x = Collection[j].x;
            pos2.y = Collection[j].y;
            pos2.z = Collection[j].z;

            // Setting force to 0 for two particles in the same location
            Vector force;
            if (vec_sepDist(pos1, pos2) < 1.0E-3) {
                force.x = 0;
                force.y = 0;
                force.z = 0;
            } else {
                double inv_dist = 1 / vec_sepDist(pos1, pos2);
                // G = M = 1
                // F_G = - (m1 * m2) * (1/ r)^2
                double force_mag = -(Collection[i].mass * Collection[j].mass) *
                                   pow(inv_dist, 2);
                Vector separation = vec_sub(pos1, pos2);
                Vector unit_sep = vec_unit(separation);
                force = vec_scalProd(force_mag, unit_sep);
            }

            force_total = vec_add(force_total, force);
        }
        Force[i] = force_total;
    }
    return Force;
}

Vector* calc_acc(Particle* Collection) {
    Vector* Accel = malloc(params.lineCount * sizeof(Vector));
    if (Accel == NULL) {
        perror("Error allocating memory for Accel!");
        exit(EXIT_FAILURE);
    }
    Vector* Force = calc_force(Collection);

    for (int i = 0; i < params.lineCount; i++) {
        // Preventing divergence for massless objects
        double invMass = 0;
        if (Collection[i].mass < 1.0E-8) {
            Vector accel;
            accel.x = 0;
            accel.y = 0;
            accel.z = 0;
            Accel[i] = accel;
        } else {
            invMass = 1 / Collection[i].mass;

            // F = m a => a = F / m = (1/m) * F
            Accel[i] = vec_scalProd(invMass, Force[i]);
        }
    }
    free(Force);
    return Accel;
}
