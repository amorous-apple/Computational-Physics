#include "calc_ener.h"

double calc_ener(Particle* Collection)
{
  double total_ener = 0.0;

  #pragma omp parallel for reduction(+:total_ener)
  for (int i = 0; i < params.lineCount; i++) {
    // Calculating and adding the kinetic energy components for particle i
    total_ener += (1.0 / 2.0) * Collection[i].mass *
                  pow(vec_mag(Collection[i].vel), 2);
  }

// Calculating and adding the gravitational potential
// energy for every particle
  #pragma omp parallel for reduction(+:total_ener)
  for (int i = 0; i < params.lineCount; i++) {
    for (int j = 0; j < params.lineCount; j++) {
      // Preventing an object form calculating the potential on itself
      if (j == i) {
        continue;
      }

      Vector pos1;
      pos1 = Collection[i].pos;

      Vector pos2;
      pos2 = Collection[j].pos;

      double separation = vec_sepDist(pos1, pos2);
      if (separation < 1E-6) {
        continue;
      } else {
        total_ener += (Collection[i].mass * Collection[j].mass) / separation;
      }
    }
  }
  return total_ener;
}

// Calculating |(E - Estart) / Estart| to see the change in energy over time
double calc_enerChange(Particle *Collection1)
{
  double energy = calc_ener(Collection1);
  if (fabs(energy) < 1e-5) {
    printf("The energy of Collection1 is very small!\n");
    printf("Energy: %.8lf\n", energy);
    printf("Starting Energy: %.8lf\n\n", params.startingEnergy);
  }
  return log(fabs((energy - params.startingEnergy) / params.startingEnergy));
}

