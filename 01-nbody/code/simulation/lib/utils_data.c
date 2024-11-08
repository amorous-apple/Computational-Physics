#include "utils_data.h"

void data_write(Particle* Collection1, FILE* pdstfile, float timeCurrent) {
    // Writing the new object positions and velocities to fileout
    for (int i = 0; i < params.lineCount; i++) {
        char dataLine[params.MAX_LINE_LENGTH];
        snprintf(dataLine, params.MAX_LINE_LENGTH,
                 "%.8lf,%.8lf,%.8lf,%.8lf,%.8lf,%.8lf,%.8lf\n", timeCurrent,
                 Collection1[i].x, Collection1[i].y, Collection1[i].z,
                 Collection1[i].vx, Collection1[i].vy, Collection1[i].vz);
        fprintf(pdstfile, "%s", dataLine);
    }
    // Add an empty line at the end of one time block
    fprintf(pdstfile, "\n\n");
}

// Writing the calculated angular moment of the system at a time point
void data_write2(double angmoment, FILE* pdstfile2, float timeCurrent) {
    char dataLine[params.MAX_LINE_LENGTH];
    snprintf(dataLine, params.MAX_LINE_LENGTH, "%.4lf,%.8lf\n", timeCurrent,
             angmoment);
    fprintf(pdstfile2, "%s", dataLine);
}

// Reading and storing the data for the bodies in Collection
void data_read(Particle* Collection, FILE* psrcfile) {
    for (int i = 0; i < params.lineCount; i++) {
        if (fscanf(psrcfile, "%lf,%lf,%lf,%lf,%lf,%lf,%lf", &Collection[i].x,
                   &Collection[i].y, &Collection[i].z, &Collection[i].vx,
                   &Collection[i].vy, &Collection[i].vz,
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
FILE* openFileout2(void) {
    FILE* pfile2 = fopen(params.fileout2, "a");
    if (pfile2 == NULL) {
        perror("Error opening output file.\n");
        exit(EXIT_FAILURE);
    }
    return pfile2;
}
