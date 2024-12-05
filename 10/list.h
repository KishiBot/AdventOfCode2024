#ifndef LIST_H
#define LIST_H

#include <stdint.h>
#include <sys/types.h>

typedef struct {
    int a;
    int b;
} pair_t;

typedef struct list_s {
    pair_t* data;
    uint32_t size;
    uint32_t capacity;
} list_t;

/*
 * Creates new list and returns its pointer.
 * If list could not be allocated, NULL is returned.
 */
list_t* list_create(int capacity);

/*
 * Frees all memory used by list itself. Stored data will remain unchanged.
 * Given pointer is invalidated.
 */
void list_destroy(list_t* list);

/*
 * Pushes itme into list.
 * If capacity is depleted, list will be reallocated.
 * 1 is returned when reallocation failes.
 * 0 is returned on success.
 */
uint8_t list_push(list_t* list, pair_t item);

/*
 * Removes item from list and returnes it.
 * NULL is returned when list does not contain item.
 */
pair_t list_pop(list_t* list, int index);

/*
 * Returns item from list with given index without popping it.
 * NULL is returned when list does not contain item.
 */
pair_t list_get(list_t* list, int index);

/*
 * Finds item in list and returns its index.
 * Returns -1 if index could not be found.
 */
pair_t list_find(list_t* list, pair_t item);

/**
 * Removes everything from list without freeing anything.
 */
void list_clear(list_t* list);

#endif
