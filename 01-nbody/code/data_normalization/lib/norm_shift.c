// Shift the data by the amount calculated with norm_shift.c
#include <stdio.h>
#include <stdlib.h>

#include "norm_position.h"

void shift_data(int argc, char* base_filename) {
    Center shift = calc_center(argc, base_filename);

    // Opening a file to read the necessary data
    char file_initial[100];
    snprintf(file_initial, sizeof(file_initial), "./data_initial/%s.csv",
             base_filename);
    FILE* pfile_i = fopen(file_initial, "r");
    if (pfile_i == NULL) {
        printf("File not found!\n");
        exit(EXIT_FAILURE);
    }

    // Opening the file to write the modified data
    char file_final[100];
    snprintf(file_final, sizeof(file_final), "./data_normalized/%s_normal.csv",
             base_filename);
    FILE* pfile_f = fopen(file_final, "a");
    if (pfile_f == NULL) {
        printf("File not found!\n");
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];
    // Initializing values in which to store read data
    double pos_x, pos_y, pos_z, mass;
    double vel_x, vel_y, vel_z;

    while (fgets(line, sizeof(line), pfile_i)) {
        // Initializing the position and velocity values to calculate new values
        // for every line in the initial file
        double shift_x, shift_y, shift_z, shift_vx, shift_vy, shift_vz = 0;
// Suppressing warnings caused by suppression of lf format specifier
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat"
        if (sscanf(line, "%lf,%lf,%lf,%lf,%lf,%lf,%lf", &pos_x, &pos_y, &pos_z,
                   &vel_x, &vel_y, &vel_z, &mass) == 7) {
            shift_x = pos_x - shift.x;
            shift_y = pos_y - shift.y;
            shift_z = pos_z - shift.z;
            shift_vx = vel_x - shift.vx;
            shift_vy = vel_y - shift.vy;
            shift_vz = vel_z - shift.vz;

            fprintf(
                pfile_f, "%.15lf,%.15lf,%.15lf,%.15lf,%.15lf,%.15lf,%.15lf\n",
                shift_x, shift_y, shift_z, shift_vx, shift_vy, shift_vz, mass);
        }
#pragma GCC diagnostic pop
    }
    printf("A shift of %s.csv has been carried out.\n", base_filename);
    fclose(pfile_i);
    fclose(pfile_f);
}
