#include "constants.h"

const double TIMEMAX = 10;

void def_params(int argc, char* argv[])
{
  if (argc != 4) {
    printf("Invalid number of command line arguments!\n");
    printf(
      "Please follow the format ./simulate <fileBase> <integrator> "
      "<timeStep>\n");
    exit(EXIT_FAILURE);
  }
  params.filename = create_filename(argv[1]);
  params.integrator = argv[2];
  params.timeStep = atof(argv[3]);
  params.stepCount = (int)(TIMEMAX / params.timeStep);
  params.lineCount = countLine(params.filename);
  params.fileout = create_fileout(argv[1], argv[2], argv[3]);
  params.fileoutCalc = create_fileoutCalc(argv[1], argv[2], argv[3]);
  params.MAX_LINE_LENGTH = 256;
}

int calc_secUsed(clock_t start, clock_t end)
{
  int secUsed = ((double)(end - start) / CLOCKS_PER_SEC);
  return secUsed;
}

char* create_filename(char* fileBase)
{
  char* filename = malloc(200);
  snprintf(filename, 200,
           "./../data_normalization/data_normalized/%s_normal.csv", fileBase);

  return filename;
}

// Creating the string to write data about the system
char* create_fileout(char* fileBase, char* integrator, char* timeStep)
{
  char* fileout = malloc(200);
  snprintf(fileout, 200, "./sim_data/data_system/%s_%s_%s.csv", fileBase,
           integrator, timeStep);

  return fileout;
}

// Creating the string to write data calculated from the system
char* create_fileoutCalc(char* fileBase, char* integrator, char* timeStep)
{
  char* fileoutCalc = malloc(200);
  snprintf(fileoutCalc, 200, "./sim_data/data_calc/%s_%s_%s_calc.csv",
           fileBase, integrator, timeStep);

  return fileoutCalc;
}

// A function that returns the number of lines in a file
int countLine(char* filename)
{
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
  fclose(pfile);
  return counter;
}
