#include "vector.h"

//Definitions of the functions from the signature
p_vector create_vector(char name[], double x, double y) {
    p_vector v = malloc(sizeof(vector));
    v->name = name;
    v->x = x;
    v->y = y;
    return v;
}

void print_vector(p_vector v) {
    printf("|   Features of the vector %s\n", v->name);
    printf("    |   coordinate along x-axis : %f\n", v->x);
    printf("    |   coordinate along y-axis : %f\n", v->y);
}

double scalar_product(p_vector v1, p_vector v2) {
    double product = 0.0;
    product = (v1->x)*(v2->x) + (v1->y)*(v2->y);
    return product;
}