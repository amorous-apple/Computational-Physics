#include "int_heun.h"

// Calculating the Heun integrator to Collection2
void calc_heun(Particle* Collection1, Particle* Collection2)
{
  const double dt = params.timeStep;
  // Calculating the initial acceleration
  Vector* Accel1 = calc_acc(Collection1);

  // Calculating the predicted velocity and position (standard Euler)
  for (int i = 0; i < params.lineCount; i++) {
    Collection2[i].vel = vec_add(Collection1[i].vel,
                                 vec_scalProd(dt, Accel1[i]));

    Collection2[i].pos =
      vec_add(Collection1[i].pos,
              vec_scalProd(dt, Collection1[i].vel));
  }

  // Calculating the acceleration at the predicted position
  Vector* Accel2 = calc_acc(Collection2);

  // Calculating the k-values for every particle and updating the position
  for (int i = 0; i < params.lineCount; i++) {
    Vector k1_pos = vec_scalProd(dt, Collection1[i].vel);
    Vector k1_vel = vec_scalProd(dt, Accel1[i]);

    Vector k2_pos = vec_scalProd(dt, Collection2[i].vel);
    Vector k2_vel = vec_scalProd(dt, Accel2[i]);

    Collection2[i].pos = vec_add(
                           Collection1[i].pos,
                           vec_scalProd(0.5, vec_add(k1_pos, k2_pos)));
    Collection2[i].vel = vec_add(
                           Collection1[i].vel,
                           vec_scalProd(0.5, vec_add(k1_vel, k2_vel)));
  }

  free(Accel1);
  free(Accel2);
}
