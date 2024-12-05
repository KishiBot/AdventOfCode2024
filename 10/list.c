#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

list_t* list_create(int capacity) {
    if (!capacity) capacity = 1;

    list_t* list = (list_t*)malloc(sizeof(list_t));
    if (!list) {
        perror("List could not be allocated");
        return NULL;
    }

    list->data = (pair_t*)malloc(sizeof(pair_t) * capacity);
    if (!list->data) {
        perror("List data could not be allocated");
        free(list);
        return NULL;
    }

    list->capacity = capacity;
    list->size = 0;

    return list;
}

void list_destroy(list_t* list) {
    if (!list) return;
    if (list->data) free(list->data);
    free(list);
}

uint8_t list_push(list_t* list, pair_t item) {
    // Realloc
    if (list->size == list->capacity) {
        list->capacity <<= 1;
        pair_t* new_data = (pair_t*)realloc(list->data, sizeof(pair_t)*list->capacity);
        if (!new_data) {
            list->capacity >>= 1;
            return 1;
        }

        list->data = new_data;
    }

    list->data[list->size++] = item;
    return 0;
}

pair_t list_pop(list_t* list, int index) {
    pair_t ret = list->data[index];

    // Move items after index
    if (index < list->size-1) {
        memmove(list->data+index, list->data+index+1, sizeof(void*)*(list->size-index));
    }

    --list->size;
    return ret;
}

pair_t list_get(list_t* list, int index) {
    return list->data[index];
}

void list_clear(list_t* list) {
    list->size = 0;
}
