#include "simulation-bh-pi.h"

int main(void) {
    double time_limit = 10000;
    double refresh_time = 2;
    int precision = 1;
    int nb_files = 2;
    char* files[nb_files];
    files[0] = "useless text but just here to use correctly the functions in the loader file";
    files[1] = "data/calculate-pi.txt";

    printf("How many digits do you want ? (n <= 6)\n");
    printf("|   ");
    scanf("%d", &precision);

    simulation_bh_pi(nb_files, files, time_limit, refresh_time, precision);
    return 0;
}