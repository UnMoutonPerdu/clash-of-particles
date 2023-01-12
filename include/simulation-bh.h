/**
 * @file simulation-bh.h
 * 
 * @brief Simple definition of the optimized simulation using binary heap and its functions.
 * 
 * @author Hugo MOUTON
 * 
 * @date 2022-02-24
 * 
 * This is a simple definition of how the optimized simulation is implemented. 
 * 
 * Here is the list of useful functions for the naive simulation :
 * 
 * - a function to draw particles in the window.
 * - a functions to do the algorithm of the simulation. 
 * 
 */
#ifndef BH_SIMULATION_H
#define BH_SIMULATION_H

#include "particle.h"
#include "event.h"
#include "loader.h"
#include "disc.h"
#include "heap.h"

/**
 * @brief Draw the particles in the window.
 * 
 * @param nb_particles the number of particles in the list of particles.
 * @param list_loader the list of particles.
 * 
 * @post After the call, particles are drawn in the window.
 * 
 */
void draw_particles(int nb_particles, list_pcles list_loader);

/**
 * @brief Executes the algorithm of the simulation.
 * 
 * @param argc the number of inputs in the command line.
 * @param argv the array of strings containing the paramaters given on the command line.
 * @param limit the time limit to do the algorithm.
 * @param refresh the refresh time when the algorithm has to refresh the window.
 * 
 * @post After the call, the algorithm has been executed.
 * 
 */
void simulation_bh(int argc, char** argv, double limit, double refresh);

#endif