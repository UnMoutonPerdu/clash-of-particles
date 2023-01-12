#include "simulation-naive.h"
#include "const.h"
#include <math.h>

//Definitions of the functions from the signature
void draw_particles(int nb_particles, list_pcles list_loader) {
    EmptySpace();
    for (int i=0; i<nb_particles; i++) {
        DrawDISC(SIZE*list_loader[i]->x, SIZE*list_loader[i]->y, SIZE*list_loader[i]->radius, list_loader[i]->color);
    }
    UpdateScreen();
}

void simulation_naive(int argc, char** argv, double limit, double refresh) {
    CreateWindow("Simulation Naive", SIZE, SIZE);
    list_pcles list_loader = loader_file(argc, argv);
    int nb_particles = loader_size(argc, argv);
    double current_time = 0.0;
    double time_limit = limit;
    double refresh_time = refresh;

    while (current_time < time_limit) {
        draw_particles(nb_particles, list_loader);
        while (current_time < refresh_time) {
            double time_next_event = refresh;
            p_particle pcle_a_involved = NULL;
            p_particle pcle_b_involved = NULL;
            int nature_event = 0;
            for (int i = 0; i<nb_particles; i++) {
                p_particle pcle_a = list_loader[i];

                double time_hwall = collision_horizontal_wall(pcle_a);
                if (time_hwall < time_next_event) {
                    time_next_event = time_hwall;
                    pcle_a_involved = pcle_a;
                    nature_event = 2;
                }
                double time_vwall = collision_vertical_wall(pcle_a);
                if (time_vwall < time_next_event) {
                    time_next_event = time_vwall;
                    pcle_a_involved = pcle_a;
                    nature_event = 1;
                }
                for (int j = i+1; j<nb_particles; j++) {
                    double time_collision = collision_two_particles(pcle_a, list_loader[j]);
                    if (time_collision < time_next_event) {
                        time_next_event = time_collision;
                        pcle_a_involved = pcle_a;
                        pcle_b_involved = list_loader[j];
                        nature_event = 3;
                    }
                }   
            }

            for (int i = 0; i<nb_particles; i++) {
                update_position(list_loader[i], time_next_event);
            }

            if (nature_event == 1) {
                update_velocity_vertical_wall(pcle_a_involved);
            }
            else if (nature_event == 2) {
                update_velocity_horizontal_wall(pcle_a_involved);
            }
            else if (nature_event == 3) {
                update_velocity_two_particles(pcle_a_involved,pcle_b_involved);
            }
            current_time += time_next_event;
        }
        refresh_time = current_time + refresh;
    }
    CloseWindow();
    deallocate_loader(list_loader, nb_particles);
}