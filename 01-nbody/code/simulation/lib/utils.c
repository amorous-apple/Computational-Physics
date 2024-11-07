#include "utils.h"

#include <time.h>

FILE* openFileout(void) {
    FILE* pfile = fopen(params.fileout, "a");
    if (pfile == NULL) {
        perror("Error opening output file.\n");
        exit(EXIT_FAILURE);
    }
    return pfile;
}
