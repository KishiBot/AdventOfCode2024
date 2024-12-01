#include <stdint.h>
#include <stdlib.h>

static void _sort(int32_t start, int32_t end, int* list);
static int32_t _partition(int32_t start, int32_t end, int* list);
void quicksort(int* list, size_t size);
