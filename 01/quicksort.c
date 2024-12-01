#include "quicksort.h"

static int32_t _partition(int32_t start, int32_t end, int* list) {
    static int32_t pivot = 0;
    static int temp = 0;

    pivot = start;
    while (start < end) {
        while (list[start] >= list[pivot] && start < end) ++start;
        while (list[end] < list[pivot] && end > pivot) --end;
        if (start < end) {
            temp = list[start];
            list[start] = list[end];
            list[end] = temp;
        }
    }

    temp = list[pivot];
    list[pivot] = list[end];
    list[end] = temp;

    return end;
}

static void _sort(int32_t start, int32_t end, int* list) {
    if (start >= end) return;

    int32_t partition = _partition(start, end, list);
    _sort(start, partition-1, list);
    _sort(partition+1, end, list);
}

void quicksort(int* list, size_t size) {
    _sort(0, size-1, list);
}
