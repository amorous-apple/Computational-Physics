#include "utils_data.h"

void data_write(Particle* Collection1, FILE* pdstfile, float timeCurrent) {
    // Writing the new object positions and velocities to fileout
    for (int i = 0; i < params.lineCount; i++) {
        char dataLine[params.MAX_LINE_LENGTH];
        snprintf(dataLine, params.MAX_LINE_LENGTH,
                 "%.3lf,%.8lf,%.8lf,%.8lf,%.8lf,%.8lf,%.8lf\n", timeCurrent,
                 Collection1[i].pos.x, Collection1[i].pos.y,
                 Collection1[i].pos.z, Collection1[i].vel.x,
                 Collection1[i].vel.y, Collection1[i].vel.z);
        fprintf(pdstfile, "%s", dataLine);
    }
    // Add two empty lines at the end of a time block
    fprintf(pdstfile, "\n\n");
}

// Writing the calculated data of the system at a time point
void data_writeCalc(double angmoment, double energy, FILE* pdstfile2,
                    float timeCurrent) {
    char dataLine[params.MAX_LINE_LENGTH];
    snprintf(dataLine, params.MAX_LINE_LENGTH, "%.4lf,%.8lf,%.8lf\n",
             timeCurrent, angmoment, energy);
    fprintf(pdstfile2, "%s", dataLine);
}

// Reading and storing the data for the bodies in Collection
void data_read(Particle* Collection, FILE* psrcfile) {
    for (int i = 0; i < params.lineCount; i++) {
        if (fscanf(psrcfile, "%lf,%lf,%lf,%lf,%lf,%lf,%lf",
                   &Collection[i].pos.x, &Collection[i].pos.y,
                   &Collection[i].pos.z, &Collection[i].vel.x,
                   &Collection[i].vel.y, &Collection[i].vel.z,
                   &Collection[i].mass) != 7) {
            printf("Error reading data for body %i \n", i);
            free(Collection);
            fclose(psrcfile);
            exit(EXIT_FAILURE);
        }
    }
}

// Opening fileout for writing data about the system
FILE* openFileout(void) {
    FILE* pfile = fopen(params.fileout, "a");
    if (pfile == NULL) {
        perror("Error opening output file.\n");
        exit(EXIT_FAILURE);
    }
    return pfile;
}
// Opening fileout for writing data calculated about the system
FILE* openFileoutCalc(void) {
    FILE* pfile2 = fopen(params.fileoutCalc, "a");
    if (pfile2 == NULL) {
        perror("Error opening output file.\n");
        exit(EXIT_FAILURE);
    }
    return pfile2;
}
