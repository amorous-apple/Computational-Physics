#ifndef INT_HERMITE_IT_H
#define INT_HERMITE_IT_H

#include "./../calc_accel.h"
#include "./../constants.h"

void calc_hermite_it(Particle *Collection1, Particle *Collection2);
void hermite_iteration(Particle *Collection1, Particle *Collection2,
                       Vector *Accel, Vector *Jerk);
#endif
