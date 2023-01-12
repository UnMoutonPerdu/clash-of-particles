/**
 * @file write-fact.c
 *
 * @brief Simple program to explain how to write
 *        text into a file
 *
 * @author C. Garion
 *
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE *p_file = NULL;

    p_file = fopen("fact.txt", "w");

    if (p_file == NULL) {
        fprintf(stderr, "Cannot write to file fact.txt!\n");
        exit(EXIT_FAILURE);
    }

    int fact = 1;

    for (int i = 0; i < 10; i++) {
        fprintf(p_file, "%d! = %d\n", i, fact);

        fact = fact * (i + 1);
    }

    fclose(p_file);

    p_file = NULL;

    return 0;
}
