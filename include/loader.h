/**
 * @file loader.h
 * 
 * @brief Simple definition of the loader and some functions.
 * 
 * @author Hugo MOUTON
 * 
 * @date 2022-02-23
 * 
 * This is a simple definition of what is considered as a loader. A loader will read a file.txt with data about particles, create particles with given features and store them into a list of pointers to particles.
 * 
 * Here is the list of useful functions for the loader :
 * 
 * - a function to create a list of pointers to particles reading a given date file.
 * - a function to deallocate a list of this type.
 * 
 */
#ifndef LOADER_H
#define LOADER_H

#include <stdlib.h>
#include <stdio.h>
#include "particle.h"

/**
 * @brief An alias to a list of pointers to particles.
 * 
 */
typedef p_particle* list_pcles;

/**
 * @brief Create a list of pointers to particles.
 * 
 * @param argc the number of inputs in the command line.
 * @param argv the array of strings containing the paramaters given on the command line.
 * 
 * @return a pointer to the beginning of a list of these particles.
 * 
 */
list_pcles loader_file(int argc, char** argv);

/**
 * @brief Computes the size of the loader.
 * 
 * @param argc the number of inputs in the command line.
 * @param argv the array of strings containing the paramaters given on the command line.
 * 
 * @return the size of the loader
 * 
 */
int loader_size(int argc, char** argv);

/**
 * @brief Deallocate the list of particles.
 * 
 * @param loader the list of particles created by the loader_file function.
 * @param size the lenght of the list.  
 * 
 * @post After the call, all memory regions used for the particles are deallocated.
 * 
 */
void deallocate_loader(list_pcles loader, int size);

#endif