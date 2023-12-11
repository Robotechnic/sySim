#include "priorityqueue/priorityqueue.h"

typedef struct priority_queue {
    size_t size;
    size_t capacity;
    void **data;
    compare_function compare;
} PriorityQueue;

#define LEFT(i) (2 * i + 1)
#define RIGHT(i) (2 * i + 2)
#define PARENT(i) ((i - 1) / 2)
#define EXTEND_CAPACITY(queue)                                                                     \
    if (queue->size == queue->capacity) {                                                          \
        queue->capacity *= 2;                                                                      \
        queue->data = realloc(queue->data, sizeof(void *) * queue->capacity);                      \
    }
#define SWAP(queue, i, j)                                                                          \
    void *tmp = queue->data[i];                                                                    \
    queue->data[i] = queue->data[j];                                                               \
    queue->data[j] = tmp;

PriorityQueue *priority_queue_new(compare_function compare, size_t capacity) {
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
    EXTEND_CAPACITY(queue)
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
	