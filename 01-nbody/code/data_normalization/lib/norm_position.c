// Calculated the position by which the data needs to be shifted for
// normalization
#include "norm_position.h"

#include <stdio.h>
#include <stdlib.h>

const int MAX_LINE_LENGTH = 200;

Center calc_center(int argc, char* base_filename) {
    if (argc != 2) {
        printf("Invalid number of arguments.\n");
        printf("Please follows the format ./normalize <xbody>.\n");
        exit(EXIT_FAILURE);
    }

    // Opening a file to read the necessary data
    char filename[100];
    snprintf(filename, sizeof(filename), "./data_initial/%s.csv",
             base_filename);
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("File not found!\n");
        exit(EXIT_FAILURE);
    }

    Center center_val;

    char line[MAX_LINE_LENGTH];
    // Initializing values in which to store read data
    double pos_x, pos_y, pos_z, mass;
    double vel_x, vel_y, vel_z;

    while (fgets(line, sizeof(line), file)) {
// Suppressing warnings caused by suppression of lf format specifier
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat"
        if (sscanf(line, "%lf,%lf,%lf,%lf,%lf,%lf,%lf", &pos_x, &pos_y, &pos_z,
                   &vel_x, &vel_y, &vel_z, &mass) == 7) {
            center_val.x += pos_x * mass;
            center_val.y += pos_y * mass;
            center_val.z += pos_z * mass;
            center_val.vx += vel_x * mass;
            center_val.vy += vel_y * mass;
            center_val.vz += vel_z * mass;
        }
#pragma GCC diagnostic pop
    }

    fclose(file);
    return center_val;
}
