#include "event.h"

//Definitions of the functions from the signature
p_event create_event(char name[], double time, p_particle pcle_a, p_particle pcle_b, int nb_collisions_a, int nb_collisions_b) {
    p_event e = malloc(sizeof(event));
    e->name = name;
    e->time = time;
    e->pcle_a = pcle_a;
    e->pcle_b = pcle_b;
    e->nb_collisions_a = nb_collisions_a;
    e->nb_collisions_b = nb_collisions_b;
    return e;
}

int type_event(p_event e) {
    int type_e = 0;
    p_particle p_a = e->pcle_a;
    p_particle p_b = e->pcle_b;
    if (p_a == NULL) {
        if (p_b == NULL) {
            type_e = 0;
        }
        else {
            type_e = 1;
        }
    }
    else {
        if (p_b == NULL) {
            type_e = 2;
        }
        else {
            type_e = 3;
        }
    }
    return type_e;
}

bool verify_event(p_event e) {
    bool validity = true;
    int type_e = type_event(e);
    p_particle p_a = e->pcle_a;
    p_particle p_b = e->pcle_b;

    if (type_e == 1) {
        if (p_b->nb_collisions != e->nb_collisions_b) {
            validity = false;
        }
    }
    else if (type_e == 2) {
        if (p_a->nb_collisions != e->nb_collisions_a) {
            validity = false;
        }
    }
    else if (type_e == 3) {
        if (p_a->nb_collisions != e->nb_collisions_a) {
            validity = false;
        }
        if (p_b->nb_collisions != e->nb_collisions_b) {
            validity = false;
        }
    }
    return validity;
}