#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "queue.h"

typedef struct {
    int item;
    void* next;
} node_t;

queue_t* q_create() {
    queue_t* q = (queue_t*)malloc(sizeof(queue_t));
    if (!q) return NULL;

    q->root = NULL;
    q->tail = NULL;

    return q;
}

void q_destroy(queue_t* q) {
    assert(q);
    while (q_pop(q));
    free(q);
    return;
}

uint8_t q_push(queue_t* q, int item) {
    if (!q) return 1;

    node_t* node = (node_t*)malloc(sizeof(node_t));
    if (!node) return 1;

    node->item = item;
    node->next = NULL;

    if (!q->root) q->root = node;
    if (!q->tail) q->tail = node;
    else {
        ((node_t*)q->tail)->next = node;
        q->tail = node;
    }

    return 0;
}

int q_pop(queue_t* q) {
    if (!q) return 0;

    node_t* node = q->root;
    if (!node) return 0;

    int ret = node->item;
    q->root = node->next;
    if (!node->next) q->tail = NULL;
    free(node);
    return ret;
}

uint64_t q_size(queue_t* q) {
    assert(q);
    node_t* node = q->root;
    uint64_t ret = 0;
    while (node) {
        ++ret;
        node = node->next;
    }
    return ret;
}
