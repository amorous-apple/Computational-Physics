#include <omp.h>
#include <stdio.h>
#include <string.h>

#include "lib/calc_angmoment.h"
#include "lib/calc_ener.h"
#include "lib/calc_rgVec.h"
#include "lib/calc_semi.h"
#include "lib/constants.h"
#include "lib/execute.h"
#include "lib/initialize.h"
#include "lib/utils_data.h"

Parameters params;

int main(int argc, char *argv[])
{
  def_params(argc, argv);

  // Initializaing a collection of data from the file
  Particle *Collection1 = initialize();
  // Initializing an empty collection
  Particle *Collection2 = initialize2();
  // memcpy to initialize masses
  memcpy(Collection2, Collection1, params.lineCount * sizeof(Particle));

  Particle *temp;

  // Removing existing data files and creating new ones to write data
  remove(params.fileout);
  FILE *fileout = openFileout();
  remove(params.fileoutCalc);
  FILE *fileoutCalc = openFileoutCalc();

  // Calculating an initial energy for later calculations
  params.startingEnergy = calc_ener(Collection1);

  // Initializing the Runge-Lenz vector and semi-major axis for a 2-body system
  if (params.lineCount == 2) {
    // Calculating the initial Runge-Lenz vector for later calculations
    params.startingRgVec = calc_rgVec(Collection1);
    // Calculating the initial semi-major axis for later calculations
    params.startingSemi = calc_semi(Collection1);
  } else {
    params.startingRgVec = -1.0;
    params.startingSemi = -1.0;
  }

  for (int i = 0; i <= params.stepCount; i++) {

    double timeCurrent = 0.0 + i * params.timeStep;
    // Writing the data of every particle to fileout
    data_write(Collection1, fileout, timeCurrent);


    // Calculating the energy change of the system
    double energy = calc_enerChange(Collection1);

    // Calculating the Runge-Lenz vector and semi-major axis for a 2-body system
    double rgVec;
    double semi;
    if (params.lineCount == 2) {
      // Calculating the rgVec change of the system
      rgVec = calc_rgVecChange(Collection1);
      // Calculating the semi-major axis change of the system
      semi = calc_semiChange(Collection1);
    } else {
      rgVec = -1.0;
      semi = -1.0;
    }

    // Writing the calculated data for the time step to fileoutCalc
    data_writeCalc(rgVec, energy, semi, fileoutCalc, timeCurrent);

    // Using Collection1 to write the next set of data to Collection2
    choose_integrator(Collection1, Collection2);

    // Swapping the buffers so that Collection1 has the new data and Collection 2 the old data
    temp = Collection2;
    Collection2 = Collection1;
    Collection1 = temp;
  }

  free(Collection1);
  free(Collection2);
}
