#ifndef NORM_POSITION_H
#define NORM_POSITION_H

extern const int MAX_LINE_LENGTH;

// Define a struct to store the center of gracity and momentum
typedef struct {
    double x;
    double y;
    double z;
    double vx;
    double vy;
    double vz;
} Center;

Center calc_center(int argc, char* base_filename);

#endif
