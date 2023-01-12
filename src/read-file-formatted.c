/**
 * @file read-file-formatted.c
 *
 * @brief Simple program to explain how to read
 *        formatted data from file
 *
 * @author C. Garion
 *
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    FILE *p_file = NULL;

    p_file = fopen(argv[1], "r");

    if (p_file == NULL) {
        fprintf(stderr, "Cannot read file %s!\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    int first_int     = 0;
    int second_int    = 0;
    int line_nb       = 1;
    int fscanf_result = 0;

    fscanf_result = fscanf(p_file, "%d - %d", &first_int, &second_int);

    while (fscanf_result != EOF) {
        if (fscanf_result != 2) {
            fprintf(stderr, "Line number %d is not syntactically correct!\n",
                     line_nb);
            exit(EXIT_FAILURE);
        }

        printf("first value at line %d: %d\n", line_nb, first_int);
        printf("second value at line %d: %d\n", line_nb, second_int);

        line_nb = line_nb + 1;
        fscanf_result = fscanf(p_file, "%d - %d", &first_int, &second_int);
    }

    fclose(p_file);

    p_file = NULL;

    return 0;
}
