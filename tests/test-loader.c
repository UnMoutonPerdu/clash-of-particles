#include "loader.h"
#include <assert.h>

void test_print_loader(list_pcles loader, int size) {
    printf("|   Test for store of particles...");
    for (int i = 0; i < size; i++) {
        print_particle(*(loader+i));
        assert (*(loader+i) != NULL);
    }
    printf("OK!\n");
}

int main(int argc, char** argv) {
    printf("|* Starting loader tests...\n");
    list_pcles list_loader = loader_file(argc, argv);
    int size_load = loader_size(argc, argv);
    test_print_loader(list_loader, size_load);
    deallocate_loader(list_loader, size_load);
    printf("  +-> OK!\n");

    return 0;
}