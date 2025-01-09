#include <omp.h>
#include <stdio.h>
#include <string.h>

#include "lib/calc_angmoment.h"
#include "lib/calc_ener.h"
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

    remove(params.fileout);
    FILE* fileout = openFileout();
    remove(params.fileoutCalc);
    FILE* fileoutCalc = openFileoutCalc();

    for (int i = 0; i <= params.stepCount; i++) {
        double timeCurrent = 0.0 + i * params.timeStep;
        // Write the data of every particle to fileout
        data_write(Collection1, fileout, timeCurrent);

        // Use Collection1 to write the next set of data to Collection2
        choose_integrator(Collection1, Collection2);

        // Collection1 = Collection2
        memcpy(Collection1, Collection2, params.lineCount * sizeof(Particle));

        // Calculating the angular moment of the system
        Vector angmoment = calc_angmoment(Collection1);
        double mag_angmoment = vec_mag(angmoment);

        // Calculating the energy of the system
        double energy = calc_ener(Collection1);

        // Writing the calculated data for the time step to fileoutCalc
        data_writeCalc(mag_angmoment, energy, fileoutCalc, timeCurrent);
    }

    free(Collection1);
    free(Collection2);

    // Ending and printing time measurement to console
    end = clock();
    secUsed = calc_secUsed(start, end);
    printf("Program took: %f CPU clock seconds \n", secUsed);
}
