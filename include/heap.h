/**
 * @file heap.h
 * 
 * @brief Simple definition of binary heap and some functions 
 * 
 * @author Hugo MOUTON 
 * 
 * @date 2022-02-24
 * 
 * This is a simple definiton of what is considered as a binary heap. We will use pointers to binary heap and its nodes.
 * 
 * Here is the list of useful functions to manipulate this strucure :
 * 
 * - a function to create an empty BH.
 * - a function to check if the BH is empty.
 * - a function to get the value at the root of the BH.
 * - a function to get the number of nodes of the BH.
 * - a function to insert a value in the BH.
 * - a function to extract the minimum value of the BH.
 * - a function to print the BH.
 * - a function to deallocate the BH. 
 * 
 */
#ifndef HEAP_H
#define HEAP_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "event.h"

/**
 * @brief An alias to the structure representing the nodes of the heap.
 * 
 */
typedef struct bh_node_event bh_node_event;

/**
 * @brief A BH is just a pointer to the root event of the heap.
 * 
 */
typedef bh_node_event* bh_node;

/**
 * @brief The structure representing the nodes of the binary heap.
 * 
 */
struct bh_node_event {
    int nb_nodes;
    p_event event;
    double event_time;
    bh_node left;
    bh_node right;
    bh_node parent;
};

/**
 * @brief Create a nil bh.
 *  
 * @return an empty bh.
 * 
 */
bh_node nil();

/**
 * @brief Is the BH empty ?
 * 
 * @param heap the bh we want to check the emptiness.
 * 
 * @return 'true' or 'false' according the emptiness of the bh.
 * 
 */
bool is_empty(bh_node heap);

/**
 * @brief The time value in the root of the bh.
 * 
 * @param heap the bh.
 * 
 * @return the value in the root of the bh.
 * 
 */
double get_value(bh_node heap);

/**
 * @brief The number of events in the bh.
 * 
 * @param heap the heap
 * 
 * @return the number of events in the heap.
 * 
 */
int get_size(bh_node heap);

/**
 * @brief Insert an event in the bh according to its time value.
 * 
 * @param heap the heap in which the event is to be inserted.
 * @param e the value to be inserted.
 * 
 * @return a heap in which there is a node containing this event. 
 *          This node is correctly placed according to the bh properties.
 *          If the value was already in the bh, no new node is inserted.
 * 
 */
bh_node insert(bh_node heap, p_event e);

/**
 * @brief Extract the event with the minimum time value in the bh (so the root).
 * 
 * @param heap the heap
 * 
 * @return the event with the minimum time value.
 * 
 */
p_event extract_min(bh_node heap);

/**
 * @brief Print the time values of the events in the level of the bh given in argument.
 * 
 * @param heap the heap
 * @param level the level of the heap
 * 
 * @post After the call, time values of the level are printed in order.
 * 
 */
void print_level(bh_node heap, int level);

/**
 * @brief Print the time values of the events of the bh.
 * 
 * @param heap the heap
 * 
 * @post After the call, time values of the heap are printed in order.
 * 
 */
void print_bh(bh_node heap);

/**
 * @brief Deallocate a bh.
 * 
 * @param heap the heap to be deallocated.
 * 
 * @post After the call, all memory regions used for the nodes are deallocated.
 * 
 */
void deallocate_bh(bh_node heap);

#endif