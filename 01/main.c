#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "quicksort.h"

int size = 1000;

int main() {
    int l1[size];
    int l2[size];

    for (int i = 0; i < size; ++i) {
        scanf("%d %d\n", &l1[i], &l2[i]);
    }

    quicksort(l1, size);
    quicksort(l2, size);

    int64_t dist = 0;
    for (int i = 0; i < size; ++i) {
        dist += abs(l1[i] - l2[i]);
    }
    printf("%ld\n", dist);

    return 0;
}
