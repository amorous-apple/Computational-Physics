#include "functions.h"

int randBit(void) {
    return rand() % 2;
}

int alphaDel(double p) {
    if (p < 0.0 || p > 1.0) {
        fprintf(stderr, "Probability must be between 0 and 1.\n");
        exit(EXIT_FAILURE);
    }
    return ((double)rand() / RAND_MAX) < p ? 1 : 0;
}
