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
    // Correct velocity
    Collection2[i].vel =
      vec_add(Collection2[i].vel,
              vec_scalProd(1.0 / 12.0,
                           vec_add(vec_scalProd(-6.0 * dt, Accel[i]),
                                   vec_add(vec_scalProd(6.0 * dt, Accel_p[i]),
                                           vec_add(vec_scalProd(-5.0 * dt2, Jerk[i]),
                                             vec_scalProd(-1.0 * dt2, Jerk_p[i]))))
                          )
             );
    // Correct position
    Collection2[i].pos =
      vec_add(Collection2[i].pos,
              vec_scalProd(1.0 / 60.0,
                           vec_add(vec_scalProd(-9.0 * dt2, Accel[i]),
                                   vec_add(vec_scalProd(9.0 * dt2, Accel_p[i]),
                                           vec_add(vec_scalProd(-7.0 * dt3, Jerk[i]),
                                             vec_scalProd(-2.0 * dt3, Jerk_p[i]))))
                          )
             );
  }

  free(Accel);
  free(Jerk);
  free(Accel_p);
  free(Jerk_p);
}
