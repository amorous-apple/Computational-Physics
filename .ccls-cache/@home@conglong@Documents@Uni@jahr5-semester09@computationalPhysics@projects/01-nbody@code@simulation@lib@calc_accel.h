#ifndef CALC_ACCEL_H
#define CALC_ACCEL_H

#include <time.h>

#include "constants.h"
#include "utils_vec.h"

Vector* calc_force(Particle* Collection);
Vector* calc_acc(Particle* Collection);
Vector* calc_jerk(Particle* Collection);
#endif
