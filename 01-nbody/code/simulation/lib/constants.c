#include "constants.h"

const double TIMEMAX = 2.0;

Parameters def_params(int argc, char* argv[]) {
    if (argc != 4) {
        printf("Invalid number of command line arguments!\n");
        printf(
            "Please follow the format ./simulate <fileBase> <integrator> "
            "<timeStep>\n");
        exit(EXIT_FAILURE);
    }
    Parameters params;
    params.filename = create_filename(argv[1]);
    params.integrator = argv[2];
    params.timeStep = atof(argv[3]);
    params.stepCount = (int)(TIMEMAX / params.timeStep);
    params.lineCount = countLine(params.filename);
    return params;
}

int calc_secUsed(clock_t start, clock_t end) {
    int secUsed = ((double)(end - start) / CLOCKS_PER_SEC);
    return secUsed;
}

char* create_filename(char* fileBase) {
    char* filename = malloc(200);
    snprintf(filename, 200,
             "./../data_normalization/data_normalized/%s_normal.csv", fileBase);

    return filename;
}

// A function that returns the number of lines in a file
int countLine(char* filename) {
    // Lines are counted in blocks of 64 kb at a time
    const int BUF_SIZE = 65536;
    FILE* pfile = fopen(filename, "r");
    if (pfile == NULL) {
        perror("Error opening file 1");
        exit(EXIT_FAILURE);
    }

    char buf[BUF_SIZE];
    int counter = 0;

    for (;;) {
        size_t chars = fread(buf, 1, BUF_SIZE, pfile);
        if (ferror(pfile)) {
            perror("Error opening file 2");
            exit(EXIT_FAILURE);
        }
        for (size_t i = 0; i < chars; i++) {
            if (buf[i] == '\n') {
                counter++;
            }
        }
        if (feof(pfile)) {
            break;
        }
    }
    return counter;
}
