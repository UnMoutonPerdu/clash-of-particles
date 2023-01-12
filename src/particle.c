#include "particle.h"
#include "vector.h"
#include <math.h>

#define EPS 1E-16

//Definitons of the functions from the signature
p_particle create_particle(char name[], double x, double y, double vx, double vy, double m, double r, int nb_collisions, int color) {
    p_particle pcle = malloc(sizeof(particle));
    pcle->name = name;
    pcle->x = x;
    pcle->y = y;
    pcle->vx = vx;
    pcle->vy = vy;
    pcle->mass = m;
    pcle->radius = r;
    pcle->nb_collisions = nb_collisions;
    pcle->color = color;

    return pcle;
}

void print_particle(p_particle pcle) {
    printf("|   Features of the particule %s\n", pcle->name);
    printf("    |   position along x-axis : %f\n", pcle->x);
    printf("    |   position along y-axis : %f\n", pcle->y);
    printf("    |   velocity along x-axis : %f\n", pcle->vx);
    printf("    |   velocity along x-axis : %f\n", pcle->vy);
    printf("    |   mass : %f\n", pcle->mass);
    printf("    |   radius : %f\n", pcle->radius);
    printf("    |   number of collisions : %d\n", pcle->nb_collisions);
    printf("    |   color : %d\n", pcle->color);
}

void update_position(p_particle pcle, double dt) {
    pcle->x = pcle->x + (pcle->vx)*dt;
    pcle->y = pcle->y + (pcle->vy)*dt;
}

double collision_vertical_wall(p_particle pcle) {
    double time = 0.0;
    if (fabs(pcle->vx) < EPS) {
        time = INFINITY;
    }
    else if (pcle->vx > 0) {
        time = (1 - pcle->x - pcle->radius)/(pcle->vx);
    }
    else {
        time = (pcle->radius - pcle->x)/(pcle->vx);
    }
    return time;
}

double collision_horizontal_wall(p_particle pcle) {
    double time = 0.0;
    if (fabs(pcle->vy) < EPS) {
        time = INFINITY;
    }
    else if (pcle->vy > 0) {
        time = (1 - pcle->y - pcle->radius)/(pcle->vy);
    }
    else {
        time = (pcle->radius - pcle->y)/(pcle->vy);
    }
    return time;
}

void update_velocity_vertical_wall(p_particle pcle) {
    pcle->vx = -pcle->vx;    
}

void update_velocity_horizontal_wall(p_particle pcle) {
    pcle->vy = -pcle->vy;    
}

double collision_two_particles(p_particle pcle1, p_particle pcle2) {
    double time = INFINITY;

    p_vector delta_pos = create_vector("delta_p", pcle2->x - pcle1->x, pcle2->y - pcle1->y);

    p_vector delta_v = create_vector("delta_v", pcle2->vx - pcle1->vx, pcle2->vy - pcle1->vy);
    
    double root = pow(scalar_product(delta_pos, delta_v),2) - scalar_product(delta_v,delta_v)*(scalar_product(delta_pos,delta_pos)-pow((pcle1->radius + pcle2->radius),2));
    
    if (root > 0) {
        time = -(scalar_product(delta_pos,delta_v) + sqrt(root))/(scalar_product(delta_v,delta_v));
    }
    
    free(delta_pos);
    free(delta_v);

    if (time>0) {
        return time;
    }

    return INFINITY;
}

void update_velocity_two_particles(p_particle pcle1, p_particle pcle2) {
    p_vector delta_pos = create_vector("delta_p", pcle2->x - pcle1->x, pcle2->y - pcle1->y);

    p_vector delta_v = create_vector("delta_v", pcle2->vx - pcle1->vx, pcle2->vy - pcle1->vy);

    double m1 = pcle1->mass;
    double m2 = pcle2->mass;
    double r1 = pcle1->radius;
    double r2 = pcle2->radius;

    pcle1->vx += ((2* m2 *scalar_product(delta_pos,delta_v) * delta_pos->x)/((m1 + m2)*pow(r1 + r2,2)));
    pcle1->vy += ((2* m2 *scalar_product(delta_pos,delta_v) * delta_pos->y)/((m1 + m2)*pow(r1 + r2,2)));

    pcle2->vx -= ((2* m1 *scalar_product(delta_pos,delta_v) * delta_pos->x)/((m1 + m2)*pow(r1 + r2,2)));
    pcle2->vy -= ((2* m1 *scalar_product(delta_pos,delta_v) * delta_pos->y)/((m1 + m2)*pow(r1 + r2,2)));

    free(delta_pos);
    free(delta_v);
}