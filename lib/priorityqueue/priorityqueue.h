#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "logger/log.h"
#include <stdbool.h>
#include <stdlib.h>

typedef struct priority_queue PriorityQueue;
typedef bool (*less_than)(void *, void *);
typedef bool (*equal)(void *, void *);
typedef void (*free_function)(void *);
typedef void (*print_function)(void *);

/**
 * @brief Initialize a new priority queue.
 *
 * @param compare the compare function
 * @param capacity the initial capacity of the priority queue
 * @return PriorityQueue* the new priority queue
 */
PriorityQueue *priority_queue_new(less_than compare, size_t capacity);

/**
 * @brief Free the priority queue.
 *
 * @param queue the priority queue
 * @param free_data a function to free the remaining elements
 */
void priority_queue_free(PriorityQueue *queue, free_function free_data);

/**
 * @brief Push a new element to the priority queue.
 *
 * @param queue the priority queue
 * @param data the data to be pushed
 */
void priority_queue_push(PriorityQueue *queue, void *data);
/**
 * @brief Pop the element with the highest priority.
 *
 * @param queue the priority queue
 * @return void* the data of the element with the highest priority
 */
void *priority_queue_pop(PriorityQueue *queue);

/**
 * @brief Return the data of the element with the highest priority without removing it.
 *
 * @param queue the priority queue
 * @return void* the data of the element with the highest priority
 */
void *priority_queue_peek(const PriorityQueue *queue);

/**
 * @brief return the size of the priority queue.
 *
 * @param queue the priority queue
 * @return size_t the size of the priority queue
 */
size_t priority_queue_size(const PriorityQueue *queue);

/**
 * @brief return true if the priority queue is empty.
 *
 * @param queue the priority queue
 * @return true if the priority queue is empty
 */
bool priority_queue_empty(const PriorityQueue *queue);

/**
 * @brief Print the priority queue.
 *
 * @param queue the priority queue
 * @param print_data the function used to print the data
 */
void priority_queue_print(const PriorityQueue *queue, print_function print_data);

/**
 * @brief Return true if the priority queue contains the element.
 *
 * @param queue the priority queue
 * @param equal_data the function used to compare the data
 * @param data the data to be compared
 * @return true if the priority queue contains the element
 */
bool priority_queue_has_element(const PriorityQueue *queue, equal equal_data, void *data);

/**
 * @brief Delete the element from the priority queue.
 *
 * @param queue the priority queue
 * @param equal_data the function used to compare the data
 * @param data the data to be compared
 */
void priority_queue_remove_element(PriorityQueue *queue, equal equal_data, void *data);

#endif // PRIORITYQUEUE_H