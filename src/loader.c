#include "loader.h"

//Definitions of the functions from the signature
list_pcles loader_file(int argc, char** argv) {
    FILE* p_file = NULL;

    p_file = fopen(argv[1], "r");

    if (p_file == NULL) {
        fprintf(stderr, "Cannot read file %s!\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    
    int fscanf_result = 0;
    int size = 0;
    char ignore[51];
    fgets(ignore,50,p_file);
    fscanf_result = fscanf(p_file, "%d", &size);
    list_pcles loader_list = calloc(size, sizeof(p_particle));

    double x = 0.0;
    double y = 0.0;
    double vx = 0.0;
    double vy = 0.0;
    double m = 0.0;
    double r = 0.0;
    int nb_collisions = 0;
    int color = 0;
    int line_nb = 3;
    int list_index = 0;

    fscanf_result = fscanf(p_file, "%lf,%lf,%lf,%lf,%lf,%lf,%d", &x, &y, &vx, &vy, &m, &r, &color);
    while (fscanf_result != EOF) {
        if (fscanf_result != 7) {
            fprintf(stderr, "Line number %d is not syntactically correct!\n",line_nb);
            exit(EXIT_FAILURE);
        }
        loader_list[list_index] = create_particle("pcle",x, y, vx, vy, m, r, nb_collisions, color);
        line_nb += 1;
        list_index += 1;
        fscanf_result = fscanf(p_file, "%lf,%lf,%lf,%lf,%lf,%lf,%d", &x, &y, &vx, &vy, &m, &r, &color);
    }
    fclose(p_file);
    p_file = NULL;

    return loader_list;
}

int loader_size(int argc, char** argv) {
    FILE* p_file = NULL;

    p_file = fopen(argv[1], "r");

    if (p_file == NULL) {
        fprintf(stderr, "Cannot read file %s!\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    
    int size = 0;
    char ignore[51];
    fgets(ignore, 50, p_file);
    fscanf(p_file, "%d", &size);
    fclose(p_file);
    p_file = NULL;
    
    return size;
}

void deallocate_loader(list_pcles loader, int size) {
    for (int i = 0; i < size; i++) {
        free(*(loader+i));
    }
    free(loader);
}