/**
 * @file test-dummy.c
 *
 * @brief Simple test executable to show how to write tests
 *
 * @author C. Garion
 *
 */

#include <assert.h>
#include <stdio.h>

void test_dummy_addition() {
    printf("  | tests for addition... ");

    assert (1 + 1 == 2);
    assert (1 + 2 == 3);

    printf("OK!\n");
}

void test_dummy_multiplication() {
    printf("  | tests for multiplication... ");

    assert (1 * 1 == 1);
    assert (2 * 2 == 4);

    printf("OK!\n");
}

int main(void) {
    printf("* Starting dummy tests...\n");

    test_dummy_addition();

    test_dummy_multiplication();

    printf("  +-> OK!\n");

    return 0;
}
