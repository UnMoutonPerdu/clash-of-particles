#include "simulation-naive.h"

int main(int argc, char** argv) {
    double time_limit = 50000;
    double refresh_time = 2;
    simulation_naive(argc, argv, time_limit, refresh_time);
    return 0;
}