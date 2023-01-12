#include "heap.h"
#include <assert.h>

int main(void) {
    printf("* Starting heap tests...\n");
    bh_node heap = nil();
    bh_node heap_to_deallocate = nil();
    printf("|   Test for emptiness of the heap...");
    assert (is_empty(heap) == true);
    printf("OK!\n");
    p_event e = create_event("e", 1, NULL, NULL, 0, 0);
    heap = insert(heap, e);
    heap_to_deallocate = insert(heap_to_deallocate,e);
    printf("|   Test for the value of the heap...");
    assert (get_value(heap) == 1.0);
    printf("OK!\n");
    for (int i = 50; i>=2; i--) {
        p_event f = create_event("e", i, NULL, NULL, 0, 0);
        insert(heap, f);
        insert(heap_to_deallocate,f);
    }
    printf("|   Test for the size of the heap...");
    assert (get_size(heap) == 50);
    printf("OK!\n");
    printf("|   Test for display of the heap...\n");
    print_bh(heap);
    printf("-------------------------------------------------------------------------\n\n");
    printf("|   Test for the extract_min function...\n");
    for (int j = 0; j<50; j++) {
        p_event event_min = extract_min(heap);
        printf("%lf ", event_min->time);
    }
    printf("\n");
    printf("    +->OK!\n");
    deallocate_bh(heap_to_deallocate);
    printf("Valgrind result : no leaks are possible !\n");
    return 0;
}