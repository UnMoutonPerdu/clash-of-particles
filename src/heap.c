#include "heap.h"
#include <math.h>

//Definitions of the functions from the signature
bh_node nil() {
    bh_node heap = NULL;
    return heap;
}

bool is_empty(bh_node heap) {
    if (heap != NULL) {
        return false;
    }
    return true;
}

double get_value(bh_node heap) {
    double value = heap->event_time;
    return value;
}

int get_size(bh_node heap) {
    return heap->nb_nodes;
}

bh_node insert(bh_node heap, p_event e) {
    if (heap == NULL) {
        bh_node new_event = malloc(sizeof(bh_node_event));
        new_event->event = e;
        new_event->event_time = e->time;
        new_event->right = NULL;
        new_event->left = NULL;
        new_event->parent = NULL;
        new_event->nb_nodes = 1;
        heap = new_event;
        return heap;
    }
    else {
        int number = (heap->nb_nodes) + 1;
        int depth = (int) log2(number);
        bh_node father_event = heap;
        for (int i = depth - 1; i>0; i--) {
            if ((number>>i & 1) == 0) {
                father_event->nb_nodes += 1;
                father_event = father_event->left;
            }
            else {
                father_event->nb_nodes += 1;
                father_event = father_event->right;
            }
        }
        if ((number & 1) == 0) {
            bh_node new_event = malloc(sizeof(bh_node_event));
            new_event->parent = father_event;
            new_event->right = NULL;
            new_event->left = NULL;
            new_event->event = e;
            new_event->event_time = e->time;
            new_event->nb_nodes = 1;
            father_event->nb_nodes += 1;
            father_event->left = new_event;
        }
        else {
            bh_node new_event = malloc(sizeof(bh_node_event));
            new_event->parent = father_event;
            new_event->right = NULL;
            new_event->left = NULL;
            new_event->event = e;
            new_event->event_time = e->time;
            new_event->nb_nodes = 1;
            father_event->nb_nodes += 1;
            father_event->right = new_event;
        }

        bh_node current_event = father_event;
        if (father_event->right != NULL) {
            current_event = current_event->right;
        }
        else {
            current_event = current_event->left;
        }
        while ((current_event->parent != NULL) && (current_event->event_time < current_event->parent->event_time)) {
            p_event temp_event = current_event->parent->event;
            double temp_event_time = current_event->parent->event_time;
            current_event->parent->event = current_event->event;
            current_event->parent->event_time = current_event->event_time;
            current_event->event = temp_event;
            current_event->event_time = temp_event_time;
            current_event = current_event->parent;
        }
    }
    return heap;
}

p_event extract_min(bh_node heap) {
    bh_node root_event = heap;
    p_event event_min = root_event->event;
    int size_heap = heap->nb_nodes;
    int depth = (int) log2(size_heap);
    bh_node father_event = heap;
    bh_node current_event = heap;

    if (size_heap == 1) {
        free(root_event);
        return event_min;
    }
    else {
        for (int i = depth - 1; i>0; i--) {
            if ((size_heap>>i & 1) == 0) {
                father_event->nb_nodes -= 1;
                father_event = father_event->left;
            }
            else {
                father_event->nb_nodes -= 1;
                father_event = father_event->right;
            }
        }
        if ((size_heap & 1) == 0) {
            current_event = father_event->left;
            father_event->left = NULL;
            father_event->nb_nodes -= 1;
        }
        else {
            current_event = father_event->right;
            father_event->right = NULL;
            father_event->nb_nodes -= 1;
        }
        root_event->event = current_event->event;
        root_event->event_time = current_event->event_time;
        current_event->parent = NULL;
        free(current_event);

        double root_value = get_value(root_event);
        double left_value = 0.0;
        double right_value = 0.0;

        if (root_event->left == NULL) {
            left_value = INFINITY;
        }
        else {
            left_value = get_value(root_event->left);
        }

        if (root_event->right == NULL) {
            right_value = INFINITY;
        }
        else {
            right_value = get_value(root_event->right);
        }

        while (root_value > left_value || root_value > right_value) {
            if (right_value < left_value) {
                p_event temp_event = root_event->event;
                double temp_event_time = root_event->event_time;
                root_event->event = root_event->right->event;
                root_event->event_time = root_event->right->event_time;
                root_event->right->event = temp_event;
                root_event->right->event_time = temp_event_time;
                root_event = root_event->right;
                if (root_event->left == NULL) {
                    left_value = INFINITY;
                }
                else {
                    left_value = get_value(root_event->left);
                }

                if (root_event->right == NULL) {
                    right_value = INFINITY;
                }
                else {
                    right_value = get_value(root_event->right);
                }
            }
            else {
                p_event temp_event = root_event->event;
                double temp_event_time = root_event->event_time;
                root_event->event = root_event->left->event;
                root_event->event_time = root_event->left->event_time;
                root_event->left->event = temp_event;
                root_event->left->event_time = temp_event_time;
                root_event = root_event->left;
                if (root_event->left == NULL) {
                    left_value = INFINITY;
                }
                else {
                    left_value = get_value(root_event->left);
                }

                if (root_event->right == NULL) {
                    right_value = INFINITY;
                }
                else {
                    right_value = get_value(root_event->right);
                }
            }
        }
        return event_min;
    }
}

void print_level(bh_node heap, int level) {
    for (int i = 0; i < level - 1; i++) {
        printf("   ");
    }

    if (is_empty(heap)) {
        printf("%snil\n", level == 0 ? "" : " +-");
        return;
    } 

    printf("%s(%lf)\n", level == 0 ? "" : " +-", heap->event_time);
    print_level(heap->left, level + 1);
    print_level(heap->right, level + 1);
}

void print_bh(bh_node heap) {
    print_level(heap, 0);
}

void deallocate_bh(bh_node heap) {
    bh_node current_node = heap;
    if (heap == NULL) {
        printf("Tree empty");
    }
    else {
        if (current_node->left != NULL) {
            deallocate_bh(current_node->left);
        }
        if (current_node->right != NULL) {
            deallocate_bh(current_node->right);
        }
        free(current_node->event);
        free(current_node);
    }
}