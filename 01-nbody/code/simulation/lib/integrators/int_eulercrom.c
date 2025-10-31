#include "int_eulercrom.h"

// Calculating the euler integrator to Collection2
void calc_eulercrom(Particle* Collection1, Particle* Collection2)
{
  Vector* Accel = calc_acc(Collection1);

  for (int i = 0; i < params.lineCount; i++) {
    Collection2[i].vel = vec_add(Collection1[i].vel,
                                 vec_scalProd(params.timeStep, Accel[i]));

    Collection2[i].pos =
      vec_add(Collection1[i].pos,
              vec_scalProd(params.timeStep, Collection2[i].vel));
  }

  free(Accel);
}
