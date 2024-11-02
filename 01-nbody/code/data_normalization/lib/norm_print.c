#include <stdio.h>

#include "norm_position.h"

void print_shift(int argc, char* argv) {
    Center val = calc_center(argc, argv);

    printf("The center of mass of the system is located at:\n");
    printf("x: %.15f\n y: %.15f\n z: %.15f \n", val.x, val.y, val.z);

    printf("The center of momentum of the system is given by:\n");
    printf("vx: %.15f\n vy: %.15f\n vz: %.15f \n", val.vx, val.vy, val.vz);
}
