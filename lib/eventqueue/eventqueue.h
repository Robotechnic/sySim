#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

#include "protocol/protocol.h"
#include "priorityqueue/priorityqueue.h"
#include "time/time.h"

typedef struct event {
    enum { TIMEOUT_EVENT, FROM_LAYER5, FROM_LAYER3, TO_LAYER_5 } type;
    double activation_time;
    side sdt;
    void *data;
} Event;

/**
 * @brief initialise a new event queue
 * 
 * @param capacity the initial capacity of the event queue
 */
void eventqueue_init(size_t capacity);

/**
 * @brief push a new send event to the event queue
 * 
 * @param delay the delay before the event is activated
 * @param sdt the even receiver
 * @param data the event data
 */
void new_from_layer5_event(double delay, side sdt, void *data);

/**
 * @brief push a new receive event to the event queue
 * 
 * @param delay the delay before the event is activated
 * @param sdt the even receiver
 * @param data the event data
 */
void new_from_layer3_event(double delay, side sdt, void *data);

/**
 * @brief push a new timeout event to the event queue
 * 
 * @param delay the delay before the timeout is activated
 * @param sdt the even receiver
 */
void new_timeout_event(double delay, side sdt);

/**
 * @brief push a new event to the event queue
 * 
 * @param delay the delay before the event is activated
 * @param sdt the even receiver
 * @param data the event data
 */
void new_to_layer5_event(double delay, side sdt, void *data);

/**
 * @brief pop the next event from the event queue
 * 
 * @return Event* the next event
 */
Event *event_queue_pop_event();

/**
 * @brief check if the event queue is empty
 * 
 * @return true if the event queue is empty
 */
bool event_queue_empty();

/**
 * @brief display an event on the standard output
 * 
 * @param event the event to display
 */
void print_event(void *event);


#endif // EVENTQUEUE_H