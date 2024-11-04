#include <stdio.h>

#include "lib/constants.h"
#include "lib/initialize.h"
#include "lib/utils.h"

Parameters params;

int main(int argc, char* argv[]) {
    // Defining time variables for measuring CPU time elapsed
    clock_t start, end;
    double secUsed;
    start = clock();

    Parameters params = def_params(argc, argv);
    Particle* Collection = initialize(argc, argv);
    Vector* Accel = calc_acc(Collection);

    printf("Test\n");
    printf("Filename: %s\n", params.filename);

    for (int i = 0; i < params.lineCount; i++) {
        printf("x_%i = %lf, a_%ix = %lf\n", i + 1, Collection[i].x, i + 1,
               Accel[i].x);
    }

    // Ending and printing time measurement to console
    end = clock();
    secUsed = calc_secUsed(start, end);
    printf("Program took: %f seconds \n", secUsed);
}
