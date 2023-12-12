#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stdlib.h>
#include "logger/log.h"

typedef struct queue Queue;
typedef void (*queue_free_fn)(void *);

/**
 * @brief create a new queue with an initial capacity
 * 
 * @param size the initial capacity of the queue
 * @return Queue* the new queue
 */
Queue *queue_create(size_t size);

/**
 * @brief free the queue
 * 
 * @param queue the queue to free
 * @param free_fn the function to free the elements of the queue
 */
void queue_free(Queue *queue, queue_free_fn free_fn);

/**
 * @brief push an element to the queue
 * 
 * @param queue the queue to push to
 * @param element the element to push
 */
void queue_push(Queue *queue, void *element);

/**
 * @brief pop an element from the queue
 * 
 * @param queue the queue to pop from
 * @return void* the element popped
 */
void *queue_pop(Queue *queue);

/**
 * @brief get the element at the front of the queue
 * 
 * @param queue the queue to get the element from
 * @return void* the element at the front of the queue
 */
void *queue_peek(Queue *queue);

/**
 * @brief get the element at the back of the queue
 * 
 * @param queue the queue to get the element from
 * @return void* the element at the back of the queue
 */
void *queue_back(Queue *queue);

/**
 * @brief get the size of the queue
 * 
 * @param queue the queue to get the size of
 * @return size_t the size of the queue
 */
size_t queue_size(Queue *queue);

/**
 * @brief check if the queue is empty
 * 
 * @param queue the queue to check
 * @return true if the queue is empty
 * @return false if the queue is not empty
 */
bool queue_empty(Queue *queue);

#endif // QUEUE_H