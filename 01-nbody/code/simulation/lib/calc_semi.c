#include "calc_rgVec.h"

// Calculating the sum of the semi major axis of all particles
double calc_semi(Particle* Collection)
{
  if (params.lineCount != 2) {
    printf("Error: Calculating semi-major axis for more than 2 bodies!\n");
    return -1;
  }

  // Calculating relative positions and velocities betweent he two bodies
  Vector r_rel = vec_sub(Collection[0].pos, Collection[1].pos);
  Vector v_rel = vec_sub(Collection[0].vel, Collection[1].vel);

  Vector angMom = vec_cross(r_rel, v_rel);
  double angMomSqr = (angMom.x * angMom.x) + (angMom.y * angMom.y) + (angMom.z * angMom.z);
  Vector rungeLenzVec = vec_sub(
                          vec_cross(v_rel, angMom),
                          vec_unit(r_rel)
                        );
  double rungeLenzVecSqr = (rungeLenzVec.x * rungeLenzVec.x) + (rungeLenzVec.y * rungeLenzVec.y) + (rungeLenzVec.z * rungeLenzVec.z);

  // Calculating and returning the semi-major axis
  return angMomSqr / (1 - rungeLenzVecSqr);

}

double calc_semiChange(Particle* Collection)
{
  double semi = calc_semi(Collection);
//   if (semi < 1e-7) {
//     printf("The semi major axis of Collection is very small!\n");
//     printf("semi: %.8lf\n", semi);
//     printf("Starting semi: %.8lf\n\n", params.startingSemi);
//   }

  return log(
           fabs(
             (semi - params.startingSemi) / params.startingSemi
           )
         );
}
