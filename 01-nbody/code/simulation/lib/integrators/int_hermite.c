#include "int_hermite.h"

void calc_hermite(Particle* Collection1, Particle* Collection2)
{
  Vector* Accel = calc_acc(Collection1);
  Vector* Jerk = calc_jerk(Collection1);

  const double dt = params.timeStep;
  const double dt2 = dt * dt;
  const double dt3 = dt2 * dt;

  // Prediction step
  for (int i = 0; i < params.lineCount; i++) {
    Vector v_old = Collection1[i].vel;
    Vector pos_old = Collection1[i].pos;

    // Predict velocity
    Vector a_term = vec_scalProd(dt, Accel[i]);
    Vector j_term = vec_scalProd(0.5 * dt2, Jerk[i]);
    Collection2[i].vel = vec_add(v_old, vec_add(a_term, j_term));

    // Predict position
    Vector pos_term1 = vec_scalProd(dt, v_old);
    Vector pos_term2 = vec_scalProd(0.5 * dt2, Accel[i]);
    Vector pos_term3 = vec_scalProd(dt3 / 6.0, Jerk[i]);
    Collection2[i].pos =
      vec_add(pos_old, vec_add(vec_add(pos_term1, pos_term2), pos_term3));
  }

  Vector* Accel_p = calc_acc(Collection2);
  Vector* Jerk_p = calc_jerk(Collection2);

  // Correction step
  for (int i = 0; i < params.lineCount; i++) {
    // Helper terms for calculation of higher order position derivatives a^(2) and a^(3)
    Vector deltaA = vec_sub(Accel[i], Accel_p[i]);
    Vector twoJ = vec_scalProd(2, Jerk[i]);
    Vector twoJ_plus_Jp = vec_add(twoJ, Jerk_p[i]);

    // Velocity correction
    Vector termA_v = vec_scalProd(dt, deltaA);
    Vector termB_v = vec_scalProd(dt2 / 3.0, twoJ_plus_Jp);
    Vector termC_v = vec_scalProd(
                       0.25, vec_add(vec_scalProd(2 * dt, deltaA),
                                     vec_scalProd(dt2, vec_add(Jerk[i], Jerk_p[i]))));
    Collection2[i].vel = vec_sub(
                           Collection2[i].vel, vec_sub(vec_add(termA_v, termB_v), termC_v));

    // Position correction
    Vector termA_p = vec_scalProd(dt2 / 4.0, deltaA);
    Vector termB_p = vec_scalProd(dt3 / 12.0, twoJ_plus_Jp);
    Vector termC_p = vec_scalProd(
                       1.0 / 20.0,
                       vec_add(vec_scalProd(2 * dt2, deltaA),
                               vec_scalProd(dt3, vec_add(Jerk[i], Jerk_p[i]))));
    Collection2[i].pos = vec_sub(
                           Collection2[i].pos, vec_sub(vec_add(termA_p, termB_p), termC_p));
  }

  free(Accel);
  free(Jerk);
  free(Accel_p);
  free(Jerk_p);
}
