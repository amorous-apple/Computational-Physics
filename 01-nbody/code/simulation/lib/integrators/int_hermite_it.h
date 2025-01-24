#ifndef INT_HERMITE_it_H
#define INT_HERMITE_it_H

#include "./../constants.h"
#include "./../calc_accel.h"

void calc_hermite_it(Particle* Collection1, Particle* Collection2);
void hermite_iteration(Particle* Collection1, Particle* Collection2, Vector* Accel,  Vector* Jerk, Vector* Accel_p,  Vector* Jerk_p);
#endif
