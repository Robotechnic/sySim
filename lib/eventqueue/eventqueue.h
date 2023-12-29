#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

#include "priorityqueue/priorityqueue.h"
#include "protocol/protocol.h"
#include "time/time.h"

typedef struct event {
    enum { TIMER_INTERUPT, FROM_LAYER5, FROM_LAYER3, FAILED_FROM_LAYER_3, TO_LAYER_5 } type;
    double activation_time;
    side sdt;
    union {
        Payload data;
        Packet *packet;
    };
} Event;

/**
 * @brief initialise a new event queue
 *
 * @param capacity the initial capacity of the event queue
 */
void eventqueue_init(size_t capacity);

/**
 * @brief free the event queue
 *
 */
void eventqueue_free();

/**
 * @brief push a new send event to the event queue
 *
 * @param delay the delay before the event is activated
 * @param sdt the even receiver
 * @param data the event data
 */
void new_from_layer5_event(double delay, side sdt, Payload data);

/**
 * @brief push a new receive event to the event queue
 *
 * @param delay the delay before the event is activated
 * @param sdt the even receiver
 * @param data the event data
 */
void new_from_layer3_event(double delay, side sdt, Packet *data);

/**
 * @brief push a new failed receive event to the event queue
 *
 * @param delay the delay before the event is activated
 * @param sdt the even receiver
 */
void new_failed_from_layer3_event(double delay, side sdt);

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
void new_to_layer5_event(double delay, side sdt, Payload data);

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
 * @brief check if the event queue has a timeout event for a given side
 *
 * @param sdt the side to check
 * @return true if the event queue has a timeout event for the given side
 */
bool has_timeout_event(side sdt);

/**
 * @brief remove the timeout event for a given side
 *
 * @param sdt the side to remove the timeout event for
 */
void remove_timeout_event(side sdt);

/**
 * @brief display an event on the standard output
 *
 * @param event the event to display
 */
void print_event(void *event);

#endif // EVENTQUEUE_H