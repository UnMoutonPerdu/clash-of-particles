#include "vector.h"
#include <assert.h>

int main(void) {
    printf("* Starting vector tests...\n");
    p_vector v1 = create_vector("v1", 2.5,-3);
    p_vector v2 = create_vector("v2", 2, 1.5);
    //print_vector(v1);
    //print_vector(v2);
    printf("|   Test for scalar product...");
    assert (scalar_product(v1,v2) == 0.5);
    printf("OK!\n");
    printf("  +-> OK!\n");
    free(v1);
    free(v2);

    return 0;
}