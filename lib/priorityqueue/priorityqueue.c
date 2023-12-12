#include "priorityqueue/priorityqueue.h"

typedef struct priority_queue {
    size_t size;
    size_t capacity;
    void **data;
    less_than compare;
} PriorityQueue;

#define LEFT(i) (2 * i + 1)
#define RIGHT(i) (2 * i + 2)
#define PARENT(i) ((i - 1) / 2)

#define SWAP(queue, i, j)                                                                          \
    void *tmp = queue->data[i];                                                                    \
    queue->data[i] = queue->data[j];                                                               \
    queue->data[j] = tmp;

PriorityQueue *priority_queue_new(less_than compare, size_t capacity) {
    PriorityQueue *queue = malloc(sizeof(PriorityQueue));
    queue->size = 0;
    queue->capacity = capacity;
    queue->data = malloc(sizeof(void *) * capacity);
    for (size_t i = 0; i < capacity; i++) {
        queue->data[i] = NULL;
    }
    queue->compare = compare;
    return queue;
}

void priority_queue_free(PriorityQueue *queue, free_function free_data) {
    for (size_t i = 0; i < queue->size; i++) {
        free_data(queue->data[i]);
    }
    free(queue->data);
    free(queue);
}

void pack(PriorityQueue *queue, size_t i) {
    size_t pi = PARENT(i);
    while (i > 0 && queue->compare(queue->data[i], queue->data[pi])) {
        SWAP(queue, i, pi)
        i = pi;
        pi = PARENT(i);
    }
}

void priority_queue_push(PriorityQueue *queue, void *data) {
    if (queue->size == queue->capacity) {
        queue->capacity *= 2;
        queue->data = realloc(queue->data, sizeof(void *) * queue->capacity);
    }
    queue->data[queue->size] = data;
    pack(queue, queue->size);
    queue->size++;
}

void *priority_queue_peek(const PriorityQueue *queue) {
    if (queue->size == 0) {
        log_fatal("PriorityQueue is empty\n");
        exit(1);
    }
    return queue->data[0];
}

void unpack(PriorityQueue *queue, size_t i) {
    size_t li = LEFT(i);
    size_t ri = RIGHT(i);
    while (i < queue->size && (li < queue->size || ri < queue->size)) {
        size_t ci = li;
        bool comp = false;
        if (ri < queue->size && queue->compare(queue->data[ri], queue->data[li])) {
            comp = true;
            ci = ri;
        }
        if (comp || queue->compare(queue->data[ci], queue->data[i])) {
            SWAP(queue, i, ci)
            i = ci;
            li = LEFT(i);
            ri = RIGHT(i);
        } else {
            return;
        }
    }
}

void *priority_queue_pop(PriorityQueue *queue) {
    void *element = priority_queue_peek(queue);
    queue->size--;
    queue->data[0] = queue->data[queue->size];
    queue->data[queue->size] = NULL;
    unpack(queue, 0);
    return element;
}

void priority_queue_print(const PriorityQueue *queue, print_function print_data) {
    printf("PriorityQueue: size = %zu, capacity = %zu\n", queue->size, queue->capacity);
    for (size_t i = 0; i < queue->size; i++) {
        printf("  ");
        print_data(queue->data[i]);
        printf("\n");
    }
}

size_t priority_queue_size(const PriorityQueue *queue) {
    return queue->size;
}

bool priority_queue_empty(const PriorityQueue *queue) {
    return queue->size == 0;
}

ssize_t get_element(const PriorityQueue *queue, equal equal_data, void *data) {
    for (size_t i = 0; i < queue->size; i++) {
        if (equal_data(queue->data[i], data)) {
            return i;
        }
    }
    return -1;
}

bool priority_queue_has_element(const PriorityQueue *queue, equal equal_data, void *data) {
    return get_element(queue, equal_data, data) != -1;
}

void priority_queue_remove_element(PriorityQueue *queue, equal equal_data, void *data) {
    ssize_t i = get_element(queue, equal_data, data);
    if (i == -1) {
        log_fatal("PriorityQueue does not contain element\n");
        exit(1);
    }
    queue->size--;
    if (i == queue->size) {
        return;
    }
    queue->data[i] = queue->data[queue->size];
    queue->data[queue->size] = NULL;
    ssize_t parent = PARENT(i);
    if (parent >= 0 && queue->compare(queue->data[i], queue->data[parent])) {
        pack(queue, i);
    } else {
        unpack(queue, i);
    }
}