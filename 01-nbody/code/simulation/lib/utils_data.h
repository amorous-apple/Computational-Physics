#ifndef UTILS_DATA_H
#define UTILS_DATA_H

#include "constants.h"

void data_write(Particle* Collection1, FILE* pdstfile, float timeCurrent);
void data_write2(double angmoment, FILE* pdstfile2, float timeCurrent);
void data_read(Particle* Collection, FILE* psrcfile);
FILE* openFileout(void);
FILE* openFileout2(void);

#endif
