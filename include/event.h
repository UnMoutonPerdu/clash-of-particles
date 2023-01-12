/**
 * @file event.h
 * 
 * @brief Simple definition of event and some function.
 * 
 * @author Hugo MOUTON
 * 
 * @date 2022-02-22
 * 
 * This is a simple definition of what is considered as an event. We also define some functions to manipulate these events. These functions will take pointers to event as parameters.
 * 
 * Here is the list of useful functions for events :
 * 
 * - a function to create an event
 * - a function to verify the validity of an event.  
 * - a function to get the type of the event.
 */
#ifndef EVENT_H
#define EVENT_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "particle.h"

/**
 * @brief An alias to the structure representing an event.
 * 
 */
typedef struct event event;

/**
 * @brief We are going to use pointers to events.
 * 
 */
typedef event* p_event;

/**
 * @brief The structure representing an event.
 * 
 */
struct event {
    char* name;
    double time;
    p_particle pcle_a;
    p_particle pcle_b;
    int nb_collisions_a;
    int nb_collisions_b;
};

/**
 * @brief Create an event.
 * 
 * @param name the name of the event.
 * @param time the instant when the event takes place.
 * @param pcle_a the first particle involved in the event.
 * @param pcle_b the second particle involved in the event.
 * @param nb_collisions_a the theorical number of collisions in which the particle_a has been involved before the event.
 * @param nb_collisions_b the theorical number of collisions in which the particle_b has been involved before the event.
 * 
 * @post If both particles are equal to NULL, we will consider the event as a refreshing event. If only one of these particles is equal to NULL, we will considered the event as a collision with a wall. Otherwise, it will be a collision between two particles.
 * 
 */
p_event create_event(char name[], double time, p_particle pcle_a, p_particle pcle_b, int nb_collisions_a, int nb_collisions_b);

/**
 * @brief Computes the type of the event.
 * 
 * @param e the event we want the type.
 * 
 * @return an integer according of the type. 0 : a refreshing event. 1 : an event involving a vertical wall. 2 : an event involving a horizontal wall. 3 : an event involving two particles.
 * 
 */
int type_event(p_event e);

/**
 * @brief Verify the validity of an event.
 * 
 * @param e the event to be verify.
 * 
 * @return a boolean true or false according of the validity of the event.
 * 
 */
bool verify_event(p_event e);

#endif