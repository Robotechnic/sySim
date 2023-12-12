#include "queue/queue.h"

typedef struct queue {
	void **queue;
	size_t front;
	size_t size;
	size_t capacity;
} Queue;

Queue *new_queue(size_t capacity) {
	Queue *queue = malloc(sizeof(Queue));
	queue->queue = malloc(sizeof(void *) * capacity);
	queue->front = 0;
	queue->size = 0;
	queue->capacity = capacity;
	return queue;
}

void queue_free(Queue *queue, queue_free_fn free_fn) {
	for (size_t i = 0; i < queue->size; i++) {
		free_fn(queue->queue[i]);
	}
	free(queue->queue);
	free(queue);
}

void queue_push(Queue *queue, void* element) {
	if (queue->size == queue->capacity) {
		log_trace("Expanding queue");
		void **new_queue = malloc(sizeof(void *) * queue->capacity * 2);
		for (size_t i = 0; i < queue->size; i++) {
			new_queue[i] = queue->queue[(queue->front + i) % queue->capacity];
		}
		free(queue->queue);
		queue->queue = new_queue;
		queue->front = 0;
		queue->capacity *= 2;
	}
	queue->queue[(queue->front + queue->size) % queue->capacity] = element;
	queue->size++;
}

void *queue_pop(Queue *queue) {
	if (queue->size == 0) {
		log_error("Queue is empty");
		exit(1);
	}
	void *element = queue->queue[queue->front];
	queue->front = (queue->front + 1) % queue->capacity;
	queue->size--;
	return element;
}

void *queue_peek(Queue *queue) {
	if (queue->size == 0) {
		log_error("Queue is empty");
		exit(1);
	}
	return queue->queue[queue->front];
}

void *queue_back(Queue *queue) {
	if (queue->size == 0) {
		log_error("Queue is empty");
		exit(1);
	}
	return queue->queue[(queue->front + queue->size - 1) % queue->capacity];
}

size_t queue_size(Queue *queue) {
	return queue->size;
}

bool queue_empty(Queue *queue) {
	return queue->size == 0;
}
