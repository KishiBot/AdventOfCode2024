#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
    if (argc == 1) return 1;
    uint64_t size = atoi(argv[1]);

    uint64_t l1[size];
    uint64_t l2[size];
    uint64_t max = 0;

    for (uint64_t i = 0; i < size; ++i) {
        scanf("%lu %lu\n", &l1[i], &l2[i]);
        if (l2[i]+1 > max) max = l2[i]+1;
    }

    uint64_t counts[max];
    memset(counts, 0, sizeof(uint64_t)*max);

    for (uint64_t i = 0; i < size; ++i) {
        ++counts[l2[i]];
    }

    uint64_t ret = 0;
    for (uint64_t i = 0; i < size; ++i) {
        if (l1[i] >= max) continue;
        ret += l1[i]*counts[l1[i]];
    }
    printf("%lu\n", ret);

    return 0;
}
