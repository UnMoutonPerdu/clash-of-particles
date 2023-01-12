/**
 * @file vector.h
 * 
 * @brief Simple definition of vector and associated functions.
 * 
 * @author Hugo MOUTON
 *  
 * @date 2022-02-22
 * 
 * This is a definition of what a vector is.
 * 
 * Here is the list of useful functions for vector :
 * 
 * - a function to create a vector.
 * - a function to print a vector.
 * - a function to computes the scalar product of two vectors.
 */
#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <stdio.h>

/**
 * @brief An alias to the structure representing a vector.
 * 
 */
typedef struct vector vector;

/**
 * @brief We are going to use pointers to vectors.
 * 
 */
typedef vector* p_vector;

/**
 * @brief The structure representing a vector.
 * 
 */
struct vector {
    char* name;
    double x;
    double y;
};

/**
 * @brief Create a vector.
 * 
 * @param name the name of the vector.
 * @param x the component along the x-axis of the vector.
 * @param y the component along the y-axis of the vector.
 * 
 * @return a vector with the given components.
 * 
 */
p_vector create_vector(char name[], double x, double y);

/**
 * @brief Print the features of a vector.
 * 
 * @param v the vector to be printed.
 * 
 * @post After the call, the vector and its features are printed.
 * 
 */
void print_vector(p_vector v);

/**
 * @brief Computes the scalar product of two vectors.
 * 
 * @param v1 the first vector.
 * @param v2 the second vector.
 * 
 * @return the scalar product of these two vectors.
 * 
 */
double scalar_product(p_vector v1, p_vector v2);

#endif