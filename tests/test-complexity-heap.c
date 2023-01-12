#include "heap.h"
#include <time.h>

int main(void) {
    printf("|   Test for complexity of insert and extract functions ...\n");
    printf("    -> Process is running ...\n");
    FILE* p_file = NULL;
    p_file = fopen("data_complexity_heap.csv", "w");
    if (p_file == NULL) {
        fprintf(stderr, "Cannot write to file data_complexity_heap.csv\n");
        exit(EXIT_FAILURE);
    }

    for (int n = 20; n<10000000; n*=2) {
        bh_node heap = nil();
        p_event e = create_event("e", 0, NULL, NULL, 0, 0);
        heap = insert(heap,e);
        clock_t start_insert = clock();
        for (int i = 1; i<n; i++) {
            p_event f = create_event("e", i, NULL, NULL, 0, 0);
            insert(heap, f);
        }
        clock_t end_insert = clock();
        double elapsed_time_insert = (double) (end_insert - start_insert) / CLOCKS_PER_SEC;
        clock_t start_extract = clock();
        for (int i = 0; i<n; i++) {
            p_event event_min = extract_min(heap);
            free(event_min);
        }
        clock_t end_extract = clock();
        double elapsed_time_extract = (double) (end_extract - start_extract) / CLOCKS_PER_SEC;
        fprintf(p_file, "%d,%lf,%lf\n", n, elapsed_time_insert, elapsed_time_extract);
    }

    fclose(p_file);
    p_file = NULL;
    printf("        -> OK!\n");

    return 0;
}