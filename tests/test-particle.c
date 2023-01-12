#include "particle.h"
#include <assert.h>
#include <math.h>
#define EPS 1E-4

void test_collision_vwall(p_particle p, double time_to_collision, double new_vx, double new_vy) {
    printf("|   Test for collision with vertical wall for %s...", p->name);
    assert ((fabs(collision_vertical_wall(p) - time_to_collision) < EPS) || (collision_vertical_wall(p) == INFINITY && time_to_collision == INFINITY));
    update_velocity_vertical_wall(p);
    assert (fabs(p->vx - new_vx) < EPS);
    assert (fabs(p->vy - new_vy) < EPS);
    printf("OK!\n");
}

void test_collision_hwall(p_particle p, double time_to_collision, double new_vx, double new_vy) {
    printf("|   Test for collision with horizontal wall for %s...", p->name);
    assert ((fabs(collision_horizontal_wall(p) - time_to_collision) < EPS) || (collision_horizontal_wall(p) == INFINITY && time_to_collision == INFINITY));
    update_velocity_horizontal_wall(p);
    assert (fabs(p->vx - new_vx) < EPS);
    assert (fabs(p->vy - new_vy) < EPS);
    printf("OK!\n");
}

void test_collision_two_particles(p_particle p1, p_particle p2, double time_to_collision, double new_vx1, double new_vy1, double new_vx2, double new_vy2) {
    printf("|   Test for collision between two particles %s and %s...", p1->name, p2->name);
    assert ((fabs(collision_two_particles(p1,p2) - time_to_collision) < EPS) || (collision_two_particles(p1,p2) == INFINITY && time_to_collision == INFINITY));
    if (time_to_collision != INFINITY) {
        update_position(p1, time_to_collision);
        update_position(p2, time_to_collision);
        update_velocity_two_particles(p1,p2);
    }
    assert (fabs(p1->vx - new_vx1) < EPS);
    assert (fabs(p1->vy - new_vy1) < EPS);
    assert (fabs(p2->vx - new_vx2) < EPS);
    assert (fabs(p2->vy - new_vy2) < EPS);
    printf("OK!\n");
}

int main(void) {
    printf("* Starting particle tests...\n");

    p_particle p1 = create_particle("p1", 0.25, 0.25, 0.5, 0, 0.5, 0.01, 1, 5); //Test create particle
    p_particle p2 = create_particle("p2", 0.25, 0.25, -0.5, 0, 0.5, 0.01, 1, 5);
    p_particle p3 = create_particle("p3", 0.25, 0.25, 0, 0.5, 0.5, 0.01, 1, 5);
    p_particle p4 = create_particle("p4", 0.25, 0.25, 0, -0.5, 0.5, 0.01, 1, 5);
    p_particle p5 = create_particle("p5", 0.25, 0.25, 0.25, -0.4, 0.5, 0.01, 1, 5);
    p_particle p6 = create_particle("p6", 0.5, 0.25, 0, 0, 0.8, 0.005, 2, 3);
    p_particle p7 = create_particle("p7", 0.75, 0.25, -0.25, 0, 0.5, 0.01, 1, 5);
    p_particle p8 = create_particle("p8", 0.6, 0.8, 0.25, -0.4, 0.8, 0.005, 1, 5);

    test_collision_vwall(p1, 1.48, -0.5, 0.0);
    test_collision_vwall(p2, 0.48, 0.5, 0.0);
    test_collision_vwall(p3, INFINITY, p3->vx, p3->vy);
    test_collision_vwall(p4, INFINITY, p4->vx, p4->vy);
    test_collision_vwall(p5, 2.96, -0.25, -0.4);

    free(p1);
    free(p2);
    free(p3);
    free(p4);
    free(p5);

    p1 = create_particle("p1", 0.25, 0.25, 0.5, 0, 0.5, 0.01, 1, 5);
    p2 = create_particle("p2", 0.25, 0.25, -0.5, 0, 0.5, 0.01, 1, 5);
    p3 = create_particle("p3", 0.25, 0.25, 0, 0.5, 0.5, 0.01, 1, 5);
    p4 = create_particle("p4", 0.25, 0.25, 0, -0.5, 0.5, 0.01, 1, 5);
    p5 = create_particle("p5", 0.25, 0.25, 0.25, -0.4, 0.5, 0.01, 1, 5);

    test_collision_hwall(p1, INFINITY, p1->vx, p1->vy);
    test_collision_hwall(p2, INFINITY, p2->vx, p2->vy);
    test_collision_hwall(p3, 1.48, 0, -0.5);
    test_collision_hwall(p4, 0.48, 0, 0.5);
    test_collision_hwall(p5, 0.6, 0.25, 0.4);

    free(p1);
    free(p2);
    free(p3);
    free(p4);
    free(p5);

    p1 = create_particle("p1", 0.25, 0.25, 0.5, 0, 0.5, 0.01, 1, 5);
    p2 = create_particle("p2", 0.25, 0.25, -0.5, 0, 0.5, 0.01, 1, 5);
    p3 = create_particle("p3", 0.25, 0.25, 0, 0.5, 0.5, 0.01, 1, 5);
    p4 = create_particle("p4", 0.25, 0.25, 0, -0.5, 0.5, 0.01, 1, 5);
    p5 = create_particle("p5", 0.25, 0.25, 0.25, -0.4, 0.5, 0.01, 1, 5);

    test_collision_two_particles(p1, p6, 0.47, -0.115385, 0, 0.384615, 0);
    free(p1);
    free(p6);
    p1 = create_particle("p1", 0.25, 0.25, 0.5, 0, 0.5, 0.01, 1, 5);
    p6 = create_particle("p6", 0.5, 0.25, 0, 0, 0.8, 0.005, 2, 3);
    test_collision_two_particles(p1, p7, 0.64, -0.25, 0.0, 0.5, 0.0);
    free(p1);
    free(p7);
    p1 = create_particle("p1", 0.25, 0.25, 0.5, 0, 0.5, 0.01, 1, 5);
    p7 = create_particle("p7", 0.75, 0.25, -0.25, 0, 0.5, 0.01, 1, 5);
    test_collision_two_particles(p1, p8, 1.352274, 0.067993, -0.329141, 0.520004, -0.194287);
    free(p1);
    free(p8);
    p1 = create_particle("p1", 0.25, 0.25, 0.5, 0, 0.5, 0.01, 1, 5);
    p8 = create_particle("p8", 0.6, 0.8, 0.25, -0.4, 0.8, 0.005, 1, 5);
    test_collision_two_particles(p7, p8, INFINITY, p7->vx, p7->vy, p8->vx, p8->vy);
    free(p1);
    free(p2);
    free(p3);
    free(p4);
    free(p5);
    free(p6);
    free(p7);
    free(p8);

    printf("  +-> OK!\n");
    return 0;
}