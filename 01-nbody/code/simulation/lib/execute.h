#ifndef EXECUTE_H
#define EXECUTE_H

#include <string.h>

#include "constants.h"

#include "integrators/int_euler.h"
#include "integrators/int_eulercrom.h"
#include "integrators/int_hermite.h"
#include "integrators/int_hermite_it.h"
#include "integrators/int_heun.h"
#include "integrators/int_middle.h"
#include "integrators/int_rk4.h"
#include "integrators/int_velver.h"

void choose_integrator(Particle *Collection1, Particle *Collection2);

#endif
