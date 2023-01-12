/**
 * @file particle.h
 *
 * @brief Simple definition of particle and some functions
 *
 * @author Hugo MOUTON
 * 
 * @date 2022-02-21
 *
 * This is a simple definition of what is considered as a particle. We also define some functions managing their evolution. These functions will take pointers to particle as parameters.
 *
 * Here is the list of useful functions for particles :
 *
 * - a function to create a particle
 * - a function that updates a particule position given dt
 * - a function that computes the expected time for a particle to collide a vertical wall (the same for an horizontal wall)
 * - a function that updates the velocity of a particle after the collision with a vertical wall (the same for an horizontal wall)
 * - a function that computes the expected time of the collision between two particles
 * - a funciton that updates velocities of these two particles after their collision
 * - a function that print particles
 */
#ifndef PARTICLE_H
#define PARTICLE_H

#include <stdlib.h>
#include <stdio.h>

/**
 * @brief An alias to the structure representing a particle.
 */
typedef struct particle particle;

/**
 * @brief We are going to use pointer to particle instead of particles themselves.
 */
typedef particle* p_particle;

/**
 * @brief The structure representing a particle.
 */
struct particle {
    char* name;
    double x, y, vx, vy, mass, radius;
    int nb_collisions, color;
};

/**
 * @brief Create a particle.
 * 
 * @param name the name of the particle.
 * @param x the position of the particle along the x-axis.
 * @param y the position of the particle along the y-axis.
 * @param vx the velocity of the particle along the x-axis.
 * @param vy the velocity of the particle along the y-axis.
 * @param m the mass of the particle.
 * @param r the radius of the particle.
 * @param nb_collisions the number of collisions in which the particle has been implicated.
 * @param color the color of the particle.
 * 
 * @return a particle with the given features.
 */
p_particle create_particle(char name[], double x, double y, double vx, double vy, double m, double r, int nb_collisions, int color);

/**
 * @brief Print the features of the particle.
 * 
 * @param pcle the particle to be printed.
 * 
 * @post After the call, the particle and its features are printed.
 * 
 */
void print_particle(p_particle pcle);

/**
 * @brief Updates the position of the particle given dt.
 * 
 * @param pcle the particle to be updated.
 * @param time the time during the particle has moved.
 * 
 * @post After the call, the particle has its new positon.
 */
void update_position(p_particle pcle, double time);

/**
 * @brief Computes the expected time for a particle to collide a vertical wall.
 * 
 * @param pcle the particle to collide.
 * 
 * @return the time until the collision.
 */
double collision_vertical_wall(p_particle pcle);

/**
 * @brief Computes the expected time for a particle to collide a horizontal wall.
 * 
 * @param pcle the particle to collide.
 * 
 * @return the time before the collision.
 */
double collision_horizontal_wall(p_particle pcle);

/**
 * @brief Updates the velocity of the particle after the collision with a vertical wall.
 * 
 * @param pcle the particle to be updated.
 * 
 * @post After the call, the particle has its new velocity.
 */
void update_velocity_vertical_wall(p_particle pcle);

/**
 * @brief Updates the velocity of the particle after the collision with a horizontal wall.
 * 
 * @param pcle the particle to be updated.
 * 
 * @post After the call, the particle has its new velocity.
 */
void update_velocity_horizontal_wall(p_particle pcle);

/**
 * @brief Computes the expected time of the collision between two particles.
 * 
 * @param pcle1 the first particle.
 * @param pcle2 the second particle.
 * 
 * @return the time before the collision.
 */
double collision_two_particles(p_particle pcle1, p_particle pcle2);

/**
 * @brief Updates the velocity of particles after their collison.
 * 
 * @param pcle1 the first particle.
 * @param pcle2 the second particle
 * 
 * @post After the call, particles have their new velocity.
 */
void update_velocity_two_particles(p_particle pcle1, p_particle pcle2);

#endif