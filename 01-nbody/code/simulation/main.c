#include <omp.h>
#include <stdio.h>
#include <string.h>

#include "lib/calc_angmoment.h"
#include "lib/constants.h"
#include "lib/execute.h"
#include "lib/initialize.h"
#include "lib/utils_data.h"

Parameters params;

int main(int argc, char* argv[]) {
    // Defining time variables for measuring CPU time elapsed
    clock_t start, end;
    double secUsed;
    start = clock();

    def_params(argc, argv);

    // Initializaing a collection of data from the file
    Particle* Collection1 = initialize();
    // Initializing an empty collection
    Particle* Collection2 = initialize2();
    // Collection2 = Collection1 (copying to initialize masses)
    memcpy(Collection2, Collection1, params.lineCount * sizeof(Particle));

    // printf("Test\n");
    // Vector* Accel = calc_acc(Collection1);
    // Vector* Force = calc_force(Collection1);
    // for (int i = 0; i < params.lineCount; i++) {
    //     printf("f_%ix: %f, f_%iy: %f, f_%iz: %f\n", i + 1, Force[i].x, i + 1,
    //            Force[i].y, i + 1, Force[i].z);
    //     printf("a_%ix: %f, a_%iy: %f, a_%iz: %f\n", i + 1, Accel[i].x, i + 1,
    //            Accel[i].y, i + 1, Accel[i].z);
    // }

    remove(params.fileout);
    FILE* fileout = openFileout();
    remove(params.fileout2);
    FILE* fileout2 = openFileout2();

    for (int i = 0; i <= params.stepCount; i++) {
        double timeCurrent = 0.0 + i * params.timeStep;
        // Write the data of every particle to fileout
        data_write(Collection1, fileout, timeCurrent);

        // Use Collection1 to write the next set of data to Collection2
        choose_integrator(Collection1, Collection2);

        // Collection1 = Collection2
        memcpy(Collection1, Collection2, params.lineCount * sizeof(Particle));

        // Calculating and writing the angular moment to fileout2
        Vector angmoment = calc_angmoment(Collection1);
        double mag_angmoment = vec_mag(angmoment);
        data_write2(mag_angmoment, fileout2, timeCurrent);
    }

    free(Collection1);
    free(Collection2);

    // Ending and printing time measurement to console
    end = clock();
    secUsed = calc_secUsed(start, end);
    printf("Program took: %f CPU clock seconds \n", secUsed);
}
