#include <stdint.h>

typedef struct {
    void* root;
    void* tail;
} queue_t;

/*
 * use capacity 0 for default capacity
 */
queue_t* q_create();
void q_destroy(queue_t* q);

/*
 * returns 0 on success, 1 otherwise
 */
uint8_t q_push(queue_t* q, int item);
int q_pop(queue_t* q);
uint64_t q_size(queue_t* q);
