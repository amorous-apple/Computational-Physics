#ifndef UTILS_DATA_H
#define UTILS_DATA_H

#include "constants.h"

void data_read(Particle* Collection, FILE* psrcfile);
void data_write(Particle* Collection1, FILE* pdstfile, float timeCurrent);
void data_writeCalc(double angmoment, double energy, FILE* pdstfile2, float timeCurrent);
FILE* openFileout(void);
FILE* openFileoutCalc(void);

#endif
