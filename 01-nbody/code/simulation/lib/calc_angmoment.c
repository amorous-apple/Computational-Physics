#include "calc_angmoment.h"

Vector calc_angmoment(Particle* Collection)
{
  Vector total_angmoment;
  total_angmoment.x = 0;
  total_angmoment.y = 0;
  total_angmoment.z = 0;

  for (int i = 0; i < params.lineCount; i++) {
    Vector pos;
    pos = Collection[i].pos;

    Vector vel;
    vel = Collection[i].vel;

    Vector angmoment = vec_cross(pos, vel);
    total_angmoment = vec_add(total_angmoment, angmoment);
  }
  return total_angmoment;
}
