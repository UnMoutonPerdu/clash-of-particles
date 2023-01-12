#include "event.h"
#include <assert.h>

void test_type_event(p_event e) {
    printf("|   Test for type of the event %s...", e->name);
    int type_e = type_event(e);
    p_particle p_a = e->pcle_a;
    p_particle p_b = e->pcle_b;
    if (type_e == 0) {
        assert (p_a == NULL && p_b == NULL);
    }
    else if (type_e == 1) {
        assert (p_a == NULL && p_b != NULL);
    }
    else if (type_e == 2) {
        assert (p_a != NULL && p_b == NULL);
    }
    else {
        assert (p_a != NULL && p_b != NULL);
    }
    printf("OK!\n");
}

void test_validity_event(p_event e, bool validity) {
    printf("|   Test for validity of the event %s...", e->name);
    bool is_valid = verify_event(e);
    assert (is_valid == validity);
    printf("OK!\n");
}

int main(void) {
    printf("* Starting event tests...\n");
    p_particle p1 = create_particle("p1", 0.25, 0.25, 0.5, 0, 0.5, 0.01, 1, 5); 
    p_particle p2 = create_particle("p2", 0.25, 0.25, -0.5, 0, 0.5, 0.01, 2, 5);
    p_particle p3 = create_particle("p3", 0.25, 0.25, 0, 0.5, 0.5, 0.01, 3, 5);
    p_particle p4 = create_particle("p4", 0.25, 0.25, 0, -0.5, 0.5, 0.01, 4, 5);
    p_event e1 = create_event("NULL_event", 0.3, NULL, NULL, 5, 3);
    p_event e2 = create_event("vertical_event", 0.2, NULL, p1, 3, 1);
    p_event e3 = create_event("horizontal_event", 0.4, p1, NULL, 2, 3);
    p_event e4 = create_event("pb_count_event", 0.1, p1, p2, 1, 3);
    p_event e5 = create_event("count_event", 0.1, p2, p3, 2, 3);

    test_type_event(e1);
    test_type_event(e2);
    test_type_event(e3);
    test_type_event(e4);
    test_type_event(e5);

    test_validity_event(e1, true);
    test_validity_event(e2, true);
    test_validity_event(e3, false);
    test_validity_event(e4, false);
    test_validity_event(e5, true);

    free(p1);
    free(p2);
    free(p3);
    free(p4);
    free(e1);
    free(e2);
    free(e3);
    free(e4);
    free(e5);
    printf("  +-> OK!\n");

    return 0;
}