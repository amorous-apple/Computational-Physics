#ifndef VEC_UTILS_H
#define VEC_UTILS_H

#include <math.h>

#include "constants.h"

Vector vec_add(Vector vec1, Vector vec2);
Vector vec_sub(Vector vec1, Vector vec2);
Vector vec_scalProd(double num, Vector vec);
double vec_separation(Vector vec1, Vector vec2);
double vec_mag(Vector vec);
Vector vec_unit(Vector vec);

#endif
