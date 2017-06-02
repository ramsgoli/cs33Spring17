#include <stdio.h>
#include <stdlib.h>

int main() {
    union ele {
        struct {
            long *p;
            long y;
        } e1;

        struct {
            long x;
            union ele *next;
        } e2;

    };

    printf("offsets: e1.p=%ld, e1.y=%ld, e2.x=%ld, e2.next=%ld");
}
