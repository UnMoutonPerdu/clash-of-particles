#include "simulation-bh.h"

#define SIZE 900

void draw_particles(int nb_particles, list_pcles list_loader) {
    EmptySpace();
    for (int i=0; i<nb_particles; i++) {
        DrawDISC(SIZE*list_loader[i]->x, SIZE*list_loader[i]->y, SIZE*list_loader[i]->radius, list_loader[i]->color);
    }
    UpdateScreen();
}

void simulation_bh(int argc, char** argv, double limit, double refresh) {
    CreateWindow("Simulation BH", SIZE, SIZE);
    list_pcles list_loader = loader_file(argc, argv);
    int nb_particles = loader_size(argc, argv);
    double current_time = 0.0;
    double former_event = 0.0;
    bh_node Q = nil();

    for (int i = 0; i<nb_particles; i++) {
        p_particle pcl_A = list_loader[i];
        p_event event_h = create_event("e", collision_horizontal_wall(pcl_A), pcl_A, NULL, pcl_A->nb_collisions, 0);
        Q = insert(Q, event_h);
        p_event event_v = create_event("e", collision_vertical_wall(pcl_A), NULL, pcl_A, 0, pcl_A->nb_collisions);
        Q = insert(Q, event_v);
        for (int j = i+1; j<nb_particles; j++) {
            p_particle pcl_B = list_loader[j];
            p_event event_two = create_event("e", collision_two_particles(pcl_A,pcl_B), pcl_A, pcl_B, pcl_A->nb_collisions, pcl_B->nb_collisions);
            Q = insert(Q, event_two);
        }
    }

    p_event refresh_event = create_event("e", 0.0, NULL, NULL, 0, 0);
    Q = insert(Q, refresh_event);

    while (current_time < limit) {
        p_event event_min = extract_min(Q);
        if (verify_event(event_min)) {
            for (int i = 0; i<nb_particles; i++) {
                update_position(list_loader[i], event_min->time - former_event);
            }
            if (type_event(event_min) == 0) {
                draw_particles(nb_particles, list_loader);
                current_time += event_min->time - former_event;
                former_event = event_min->time;
                p_event new_refresh_event = create_event("e", former_event + refresh, NULL, NULL, 0, 0);
                Q = insert(Q, new_refresh_event);
            }

            else if (type_event(event_min) == 1) {
                current_time += event_min->time - former_event;
                former_event = event_min->time;
                update_velocity_vertical_wall(event_min->pcle_b);
                event_min->pcle_b->nb_collisions += 1;
                p_event new_event_h = create_event("e", current_time + collision_horizontal_wall(event_min->pcle_b), event_min->pcle_b, NULL, event_min->pcle_b->nb_collisions, 0);
                Q = insert(Q,new_event_h);
                p_event new_event_v = create_event("e", current_time + collision_vertical_wall(event_min->pcle_b), NULL, event_min->pcle_b, 0, event_min->pcle_b->nb_collisions);
                Q = insert(Q, new_event_v);
                for (int j = 0; j<nb_particles; j++) {
                    p_particle pcl_B = list_loader[j];
                    if (pcl_B != event_min->pcle_b) {
                        p_event new_event_two = create_event("e", current_time + collision_two_particles(event_min->pcle_b,pcl_B), event_min->pcle_b, pcl_B, event_min->pcle_b->nb_collisions, pcl_B->nb_collisions);
                        Q = insert(Q, new_event_two);
                    }
                }
            }

            else if (type_event(event_min) == 2) {
                current_time += event_min->time - former_event;
                former_event = event_min->time;
                update_velocity_horizontal_wall(event_min->pcle_a);
                event_min->pcle_a->nb_collisions += 1;
                p_event new_event_h = create_event("e", current_time + collision_horizontal_wall(event_min->pcle_a), event_min->pcle_a, NULL, event_min->pcle_a->nb_collisions, 0);
                Q = insert(Q,new_event_h);
                p_event new_event_v = create_event("e", current_time + collision_vertical_wall(event_min->pcle_a), NULL, event_min->pcle_a, 0, event_min->pcle_a->nb_collisions);
                Q = insert(Q, new_event_v);
                for (int j = 0; j<nb_particles; j++) {
                    p_particle pcl_A = list_loader[j];
                    if (pcl_A != event_min->pcle_a) {
                        p_event new_event_two = create_event("e", current_time + collision_two_particles(event_min->pcle_a,pcl_A), event_min->pcle_a, pcl_A, event_min->pcle_a->nb_collisions, pcl_A->nb_collisions);
                        Q = insert(Q, new_event_two);
                    }
                }
            }

            else if (type_event(event_min) == 3) {
                current_time += event_min->time - former_event;
                former_event = event_min->time;
                update_velocity_two_particles(event_min->pcle_a, event_min->pcle_b);
                event_min->pcle_a->nb_collisions += 1;
                event_min->pcle_b->nb_collisions += 1;
                p_event new_event_h = create_event("e", current_time + collision_horizontal_wall(event_min->pcle_a), event_min->pcle_a, NULL, event_min->pcle_a->nb_collisions, 0);
                p_event new_event_h2 = create_event("e", current_time + collision_horizontal_wall(event_min->pcle_b), event_min->pcle_b, NULL, event_min->pcle_b->nb_collisions, 0);
                Q = insert(Q, new_event_h);
                Q = insert(Q, new_event_h2);
                p_event new_event_v = create_event("e", current_time + collision_vertical_wall(event_min->pcle_a), NULL, event_min->pcle_a, 0, event_min->pcle_a->nb_collisions);
                p_event new_event_v2 = create_event("e", current_time + collision_vertical_wall(event_min->pcle_b), NULL, event_min->pcle_b, 0, event_min->pcle_b->nb_collisions);
                Q = insert(Q, new_event_v);
                Q = insert(Q, new_event_v2);
                for (int j = 0; j<nb_particles; j++) {
                    p_particle pcl = list_loader[j];
                    if (pcl != event_min->pcle_b) {
                        p_event new_event_two = create_event("e", current_time + collision_two_particles(event_min->pcle_b,pcl), event_min->pcle_b, pcl, event_min->pcle_b->nb_collisions, pcl->nb_collisions);
                        Q = insert(Q, new_event_two);
                    }
                    if (pcl != event_min->pcle_a) {
                        p_event new_event_two = create_event("e", current_time + collision_two_particles(event_min->pcle_a,pcl), event_min->pcle_a, pcl, event_min->pcle_a->nb_collisions, pcl->nb_collisions);
                        Q = insert(Q, new_event_two);
                    }
                }
            }
        }
        free(event_min);
    }
    CloseWindow();
    deallocate_bh(Q);
    deallocate_loader(list_loader, nb_particles);
}