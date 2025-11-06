#include "int_heun.h"

// Calculating the Heun integrator to Collection2
void calc_heun(Particle* Collection1, Particle* Collection2)
{
  const double dt = params.timeStep;

  // Initializing new Collections to store k pos and vel
  Particle *k1_Collection = initialize2();
  Particle *k2_Collection = initialize2();

  // Calculating the initial acceleration
  Vector* Accel1 = calc_acc(Collection1);

  // Calculating k1
  for (int i = 0; i < params.lineCount; i++) {
    k1_Collection[i].vel = vec_scalProd(dt, Accel1[i]);
    k1_Collection[i].pos = vec_scalProd(dt, Collection1[i].vel);
  }

  // Calculating and storing the predicted position and velocity in Collection2
  for (int i = 0; i < params.lineCount; i++) {
    Collection2[i].vel = vec_add(Collection1[i].vel, k1_Collection[i].vel);
    Collection2[i].pos = vec_add(Collection1[i].pos, k1_Collection[i].pos);
  }

  // Calculating the predicted acceleration at t + dt and the predicted pos and vel
  Vector* Accel2 = calc_acc(Collection2);

  // Calculting k2
  for (int i = 0; i < params.lineCount; i++) {
    k2_Collection[i].vel = vec_scalProd(dt, Accel2[i]);
    k2_Collection[i].pos = vec_scalProd(dt, Collection2[i].vel);
  }

  // Calculating the final particle positions and velocities
  for (int i = 0; i < params.lineCount; i++) {
    Collection2[i].pos = vec_add(
                           Collection1[i].pos,
                           vec_scalProd(0.5, vec_add(k1_Collection[i].pos, k2_Collection[i].pos)));
    Collection2[i].vel = vec_add(
                           Collection1[i].vel,
                           vec_scalProd(0.5, vec_add(k1_Collection[i].vel, k2_Collection[i].vel)));
  }

  free(k1_Collection);
  free(k2_Collection);
  free(Accel1);
  free(Accel2);
}
