#include "lib/norm_print.h"
#include "lib/norm_shift.h"

int main(int argc, char* argv[]) {
    // printf("Main successfully run :D \n");

    print_shift(argc, argv[1]);
    shift_data(argc, argv[1]);

    // printf("Main successfully run to end :D \n");
}
