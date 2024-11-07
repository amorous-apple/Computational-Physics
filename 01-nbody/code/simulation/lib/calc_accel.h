#ifndef CALC_ACCEL_H
#define CALC_ACCEL_H

#include <time.h>

#include "constants.h"
#include "vec_utils.h"

Vector* calc_force(Particle* Collection);
Vector* calc_acc(Particle* Collection);

#endif
