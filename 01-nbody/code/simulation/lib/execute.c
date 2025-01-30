#include "execute.h"

void choose_integrator(Particle* Collection1, Particle* Collection2) {
    if (strcmp(params.integrator, "euler") == 0) {
        calc_euler(Collection1, Collection2);
    } else if (strcmp(params.integrator, "eulercrom") == 0) {
        calc_eulercrom(Collection1, Collection2);
    } else if (strcmp(params.integrator, "mid") == 0) {
        calc_middle(Collection1, Collection2);
    } else if (strcmp(params.integrator, "velver") == 0) {
        calc_velver(Collection1, Collection2);
    } else if (strcmp(params.integrator, "hermite") == 0) {
        calc_hermite(Collection1, Collection2);
    } else {
        printf("Invalid integrator. Try again m9\n");
        printf(
            "Valid options include: 'euler', 'eulercrom', 'mid', 'velver'\n");
        exit(EXIT_FAILURE);
    }
}
