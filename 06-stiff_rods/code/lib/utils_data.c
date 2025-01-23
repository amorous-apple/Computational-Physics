#include "utils_data.h"

char *create_filename(char *fileBase) {
    char *filename = malloc(200 * sizeof(char));
    if (filename == NULL) {
        perror("Error allocating memory for fileName!\n");
    }

    snprintf(filename, 200, "./data/%s.csv", fileBase);
    return filename;
}

void data_write(char *fileBase, unsigned long int **data) {
    char *filename = create_filename(fileBase);
    remove(filename);

    FILE *dstFile = fopen(filename, "a");
    if (dstFile == NULL) {
        printf("Error opening file to write %s!\n", fileBase);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < NUM_DATA_POINTS - 1; i++) {
        char dataLine[200];
        snprintf(dataLine, 200, "%li,%li,%li,%li\n", data[i][0], data[i][1],
                 data[i][2], data[i][3]);
        fprintf(dstFile, "%s", dataLine);
    }
}
