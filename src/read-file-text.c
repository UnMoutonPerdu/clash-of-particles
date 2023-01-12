/**
 * @file read-file-text.c
 *
 * @brief Simple program to explain how to read
 *        text lines from file
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

    // declaration of a buffer of 81 chars: we suppose that each line
    // of the file has no more than 80 chars and we add 1 char for the
    // final '\0' character
    char buffer[81];
    int  line = 0;

    // while not having encountered end of file, read lines
    while (fgets(buffer, 80, p_file) != NULL) {
        line++;

        printf("%2d: %s", line, buffer);
    }

    fclose(p_file);

    p_file = NULL;

    return 0;
}
