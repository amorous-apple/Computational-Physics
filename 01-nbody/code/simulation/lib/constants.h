#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>


extern const double TIMEMAX;

typedef struct {
	double x, y, z;
	double vx, vy, vz;
	double mass;
} Particle;

typedef struct {
	double x;
	double y;
	double z;
} Vector;

typedef struct {
	char* filename;
	char* integrator;
	double timeStep;
	int stepCount;
	int lineCount;
	char* fileout;
	char* fileout2;
	int MAX_LINE_LENGTH;
} Parameters;

extern Parameters params;

void def_params(int argc, char* argv[]);
int calc_secUsed(clock_t start, clock_t end);
char* create_filename(char* fileBase);
char* create_fileout(char* fileBase, char* integrator, char* timeStep);
char* create_fileout2(char* fileBase, char* integrator, char* timeStep);
int countLine(char* filename);

#endif
