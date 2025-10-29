#include <omp.h>
#include <stdio.h>
#include <string.h>

#include "lib/calc_angmoment.h"
#include "lib/calc_ener.h"
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

  for (int i = 0; i <= params.stepCount; i++) {

    double timeCurrent = 0.0 + i * params.timeStep;
    // Writing the data of every particle to fileout
    data_write(Collection1, fileout, timeCurrent);

    // Calculating the angular moment of the system
    Vector angmoment = calc_angmoment(Collection1);
    double mag_angmoment = vec_mag(angmoment);

    // Calculating the energy of the system
    double energy = calc_ener(Collection1);

    // Writing the calculated data for the time step to fileoutCalc
    data_writeCalc(mag_angmoment, energy, fileoutCalc, timeCurrent);

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
