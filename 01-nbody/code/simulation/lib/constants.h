#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern const double TIMEMAX;

typedef struct {
  double x;
  double y;
  double z;
} Vector;

typedef struct {
  Vector pos;
  Vector vel;
  double mass;
} Particle;

typedef struct {
  char *filename;
  char *integrator;
  double timeStep;
  int stepCount;
  int lineCount;
  char *fileout;
  char *fileoutCalc;
  int MAX_LINE_LENGTH;
  double startingEnergy;
  double startingRgVec;
  double startingSemi;
} Parameters;

extern Parameters params;

void def_params(int argc, char *argv[]);
int calc_secUsed(clock_t start, clock_t end);
char *create_filename(char *fileBase);
char *create_fileout(char *fileBase, char *integrator, char *timeStep);
char *create_fileoutCalc(char *fileBase, char *integrator, char *timeStep);
int countLine(char *filename);

#endif
