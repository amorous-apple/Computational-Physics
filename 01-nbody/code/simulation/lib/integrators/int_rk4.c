#include "int_rk4.h"

// Calculating the Runge-Kutta 4 integrator to Collection2
void calc_rk4(Particle* Collection1, Particle* Collection2)
{
  const double dt = params.timeStep;

  // Initializing new Collections to store k pos and vel
  Particle *k1_Collection = initialize2();
  Particle *k2_Collection = initialize2();
  Particle *k3_Collection = initialize2();
  Particle *k4_Collection = initialize2();

  // Calculating the initial acceleration
  Vector* Accel1 = calc_acc(Collection1);

  // ============================================
  // k1 BLOCK
  // Calculating k1
  for (int i = 0; i < params.lineCount; i++) {
    k1_Collection[i].vel = vec_scalProd(dt, Accel1[i]);
    k1_Collection[i].pos = vec_scalProd(dt, Collection1[i].vel);
  }
  // ============================================



  // ============================================
  // k2 BLOCK
  //
  // Calculating and storing the predicted position and velocity in Collection2 (t = t + 0.5 dt, pos and vel + 0.5 k1)
  for (int i = 0; i < params.lineCount; i++) {
    Collection2[i].vel = vec_add(Collection1[i].vel, vec_scalProd(0.5, k1_Collection[i].vel));
    Collection2[i].pos = vec_add(Collection1[i].pos, vec_scalProd(0.5, k1_Collection[i].pos));
  }

  // Calculating the predicted acceleration
  Vector* Accel2 = calc_acc(Collection2);

  // Calculating k2
  for (int i = 0; i < params.lineCount; i++) {
    k2_Collection[i].vel = vec_scalProd(dt, Accel2[i]);
    k2_Collection[i].pos = vec_scalProd(dt, Collection2[i].vel);
  }
  // ============================================



  // ============================================
  // k3 BLOCK
  //
  // Calculating and storing the predicted position and velocity in Collection2 (t = t + 0.5 dt, pos and vel + 0.5 k2)
  for (int i = 0; i < params.lineCount; i++) {
    Collection2[i].vel = vec_add(Collection1[i].vel, vec_scalProd(0.5, k2_Collection[i].vel));
    Collection2[i].pos = vec_add(Collection1[i].pos, vec_scalProd(0.5, k2_Collection[i].pos));
  }

  // Calculating the predicted acceleration
  Vector* Accel3 = calc_acc(Collection2);

  // Calculating k3
  for (int i = 0; i < params.lineCount; i++) {
    k3_Collection[i].vel = vec_scalProd(dt, Accel3[i]);
    k3_Collection[i].pos = vec_scalProd(dt, Collection2[i].vel);
  }
  // ============================================



  // ============================================
  // k4 BLOCK
  //
  // Calculating and storing the predicted position and velocity in Collection2 (t = t + dt, pos and vel + k3)
  for (int i = 0; i < params.lineCount; i++) {
    Collection2[i].vel = vec_add(Collection1[i].vel, k3_Collection[i].vel);
    Collection2[i].pos = vec_add(Collection1[i].pos, k3_Collection[i].pos);
  }

  // Calculating the predicted acceleration
  Vector* Accel4 = calc_acc(Collection2);

  // Calculating k3
  for (int i = 0; i < params.lineCount; i++) {
    k4_Collection[i].vel = vec_scalProd(dt, Accel4[i]);
    k4_Collection[i].pos = vec_scalProd(dt, Collection2[i].vel);
  }
  // ============================================



  // Calculating the final particle positions and velocities using RK4 and the calculated kx values
  for (int i = 0; i < params.lineCount; i++) {
    Collection2[i].pos = vec_add(
                           Collection1[i].pos,
                           vec_add(vec_scalProd((1.0 / 6.0), k1_Collection[i].pos),
                                   vec_add(vec_scalProd((1.0 / 3.0), k2_Collection[i].pos),
                                           vec_add(vec_scalProd((1.0 / 3.0), k3_Collection[i].pos),
                                             vec_scalProd((1.0 / 6.0), k4_Collection[i].pos)))));
    Collection2[i].vel = vec_add(
                           Collection1[i].vel,
                           vec_add(vec_scalProd((1.0 / 6.0), k1_Collection[i].vel),
                                   vec_add(vec_scalProd((1.0 / 3.0), k2_Collection[i].vel),
                                           vec_add(vec_scalProd((1.0 / 3.0), k3_Collection[i].vel),
                                             vec_scalProd((1.0 / 6.0), k4_Collection[i].vel)))));
  }

  free(k1_Collection);
  free(k2_Collection);
  free(k3_Collection);
  free(k4_Collection);
  free(Accel1);
  free(Accel2);
  free(Accel3);
  free(Accel4);
}
