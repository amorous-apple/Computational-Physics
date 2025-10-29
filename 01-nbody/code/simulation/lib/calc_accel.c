#include "calc_accel.h"

Vector* calc_force(Particle* Collection)
{
  Vector* Force = malloc(params.lineCount * sizeof(Vector));
  if (Force == NULL) {
    perror("Error allocating memory for Force!");
    exit(EXIT_FAILURE);
  }
  int n = params.lineCount;

  #pragma omp parallel for
  for (int i = 0; i < n; i++) {
    Vector force_total;
    force_total.x = 0;
    force_total.y = 0;
    force_total.z = 0;

    Vector pos1;
    pos1 = Collection[i].pos;

    for (int j = 0; j < n; j++) {
      // Preventing an object form calculating the force on itself
      if (j == i) {
        continue;
      }

      Vector pos2;
      pos2 = Collection[j].pos;

      // Setting force to 0 for two particles in the same location
      Vector force;
      if (vec_sepDist(pos1, pos2) < 1.0E-3) {
        force.x = 0;
        force.y = 0;
        force.z = 0;
      } else {
        double inv_dist = 1.0 / vec_sepDist(pos1, pos2);
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

Vector* calc_acc(Particle* Collection)
{
  Vector* Accel = malloc(params.lineCount * sizeof(Vector));
  if (Accel == NULL) {
    perror("Error allocating memory for Accel!");
    exit(EXIT_FAILURE);
  }
  Vector* Force = calc_force(Collection);

  // #pragma omp parallel for
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

// calculate derivative of accel (jerk)
Vector* calc_jerk(
  Particle* Collection)    // möglicher Fehler bei VZ von jerk_mag
{
  Vector* Jerk = malloc(params.lineCount * sizeof(Vector));
  if (Jerk == NULL) {
    perror("Error allocating memory for Jerk!\n");
    exit(EXIT_FAILURE);
  }

  #pragma omp parallel for
  for (int i = 0; i < params.lineCount; i++) {
    Vector jerk_total;
    jerk_total.x = 0;
    jerk_total.y = 0;
    jerk_total.z = 0;

    Vector pos1;
    pos1 = Collection[i].pos;

    Vector vel1;
    vel1 = Collection[i].vel;

    for (int j = 0; j < params.lineCount; j++) {
      // Preventing an object from calculating the jerk on itself
      if (j == i) {
        continue;
      }

      Vector pos2;
      pos2 = Collection[j].pos;

      Vector vel2;
      vel2 = Collection[j].vel;

      Vector jerk;
      Vector rSeperation = vec_sub(pos1, pos2);
      double rSeperationMag = vec_mag(rSeperation);
      Vector vSeperation = vec_sub(vel1, vel2);

      // Setting jerk to 0 for two particles in the same location
      if (rSeperationMag < 1.0E-3) {
        jerk.x = 0;
        jerk.y = 0;
        jerk.z = 0;
      } else {
        double inv_dist = 1.0 / vec_sepDist(pos1, pos2);
        // G = M = 1

        double jerk_magv = (Collection[j].mass) * pow(inv_dist, 3);
        double jerk_magr = 3.0 * (Collection[j].mass) *
                           vec_dot(vSeperation, rSeperation) *
                           pow(inv_dist, 5);

        jerk = vec_sub(vec_scalProd(jerk_magv, vSeperation),
                       vec_scalProd(jerk_magr, rSeperation));
      }

      jerk_total = vec_add(jerk_total, jerk);
    }
    Jerk[i] = jerk_total;
  }
  return Jerk;
}
