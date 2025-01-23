#include "functions.h"

int fiftyFifty(void) { return rand() % 2; }

int randomBit(double p) {
    if (p < 0.0 || p > 1.0) {
        perror("Probability must be between 0 and 1.\n");
        exit(EXIT_FAILURE);
    }
    return ((double)rand() / RAND_MAX) < p ? 1 : 0;
}

double alphaDel(int numRods) {
<<<<<<< HEAD
    double probability =
        ((double)numRods / (2.0 * SYSTEM_SIZE * SYSTEM_SIZE) * ACTIVITY_INVERSE);
=======
    double probability = ((double)numRods / (2.0 * SYSTEM_SIZE * SYSTEM_SIZE) *
                          ACTIVITY_INVERSE);
>>>>>>> d6daaf5016a3013b23044594afb3a8d5eef187c9
    return probability > 1 ? 1.0 : probability;
}

double alphaIns(int numRods) {
    double probability =
        (2.0 * SYSTEM_SIZE * SYSTEM_SIZE / (numRods + 1.0) * ACTIVITY);
    return probability > 1 ? 1.0 : probability;
}

int randomCoord() { return rand() % SYSTEM_SIZE; }
