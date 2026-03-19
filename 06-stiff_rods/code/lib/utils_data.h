#ifndef UTILS_H
#define UTILS_H

#include "init.h"

#include <stdio.h>
#include <stdlib.h>

char *create_filename(char *fileBase);
void data_write(char *fileBase, unsigned long int **data);
void positions_write(char *fileBase, Position *rods, int count);

#endif
