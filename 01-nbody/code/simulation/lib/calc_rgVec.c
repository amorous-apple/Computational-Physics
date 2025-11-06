#include "calc_rgVec.h"

// Calculating the absolute value of the runge-lenz Vector
double calc_rgVec(Particle* Collection)
{
  if (params.lineCount != 2) {
    printf("Error: Calculating Runge-Lenz vector for more than 2 bodies!\n");
    return -1;
  }

  // Calculating relative positions and velocities betweent he two bodies
  Vector r_rel = vec_sub(Collection[0].pos, Collection[1].pos);
  Vector v_rel = vec_sub(Collection[0].vel, Collection[1].vel);

  Vector angMom = vec_cross(r_rel, v_rel);
  Vector rungeLenzVec = vec_sub(
                          vec_cross(v_rel, angMom),
                          vec_unit(r_rel)
                        );
  return vec_mag(rungeLenzVec);
}

double calc_rgVecChange(Particle* Collection)
{
  double rgVec = calc_rgVec(Collection);
//   if (params.startingRgVec < 1e-7) {
//     printf("The startingRgVec of Collection is very small!\n");
//     printf("rgVec: %.8lf\n", rgVec);
//     printf("Starting rgVec: %.8lf\n\n", params.startingRgVec);
//   }

  return log(
           fabs(
             // (rgVec - params.startingRgVec) / params.startingRgVec
             (rgVec - params.startingRgVec)
           )
         );
}
