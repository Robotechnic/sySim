#include "eventqueue/eventqueue.h"

static PriorityQueue *event_queue = NULL;

void free_event(void *event) {
    free(event);
}

bool compare_event(void *a, void *b) {
    const Event *event_a = (Event *)a;
    const Event *event_b = (Event *)b;
    return event_a->activation_time < event_b->activation_time;
}

void eventqueue_init(size_t capacity) {
    if (event_queue != NULL) {
        priority_queue_free(event_queue, free_event);
    }
    event_queue = priority_queue_new(compare_event, capacity);
}

void eventqueue_free() {
    priority_queue_free(event_queue, free_event);
    event_queue = NULL;
}

void new_from_layer5_event(double delay, side sdt, Payload data) {
    Event *event = malloc(sizeof(Event));
    event->type = FROM_LAYER5;
    event->activation_time = delay + get_time();
    event->sdt = sdt;
    event->data = data;
    priority_queue_push(event_queue, event);
}

void new_from_layer3_event(double delay, side sdt, Packet *data) {
    log_trace("LAYER_3 TO %c in %lf", side_to_char(sdt), delay);
    Event *event = malloc(sizeof(Event));
    event->type = FROM_LAYER3;
    event->activation_time = delay + get_time();
    event->sdt = sdt;
    event->packet = data;
    priority_queue_push(event_queue, event);
}

void new_timeout_event(double delay, side sdt) {
    log_trace("TIMEOUT EVENT FROM %c in %lf", side_to_char(sdt), delay);
    Event *event = malloc(sizeof(Event));
    event->type = TIMER_INTERUPT;
    event->activation_time = delay + get_time();
    event->sdt = sdt;
    event->packet = NULL;
    priority_queue_push(event_queue, event);
}

void new_to_layer5_event(double delay, side sdt, Payload data) {
    Event *event = malloc(sizeof(Event));
    event->type = TO_LAYER_5;
    event->activation_time = delay + get_time();
    event->sdt = sdt;
    event->data = data;
    priority_queue_push(event_queue, event);
}

void print_event(void *event) {
    const Event *e = (Event *)event;
    switch (e->type) {
        case TIMER_INTERUPT:
            printf("TIMEOUT_EVENT ");
            break;
        case FROM_LAYER5:
            printf("FROM_LAYER5    ");
            break;
        case FROM_LAYER3:
            printf("FROM_LAYER3 ");
            break;
        case TO_LAYER_5:
            printf("TO_LAYER_5 ");
    }
    printf("(%c) at %f\n", side_to_char(e->sdt), e->activation_time);
}

Event *event_queue_pop_event() {
    Event *ev = priority_queue_pop(event_queue);
    if (ev->activation_time > get_time()) {
        update_time(ev->activation_time);
    }
    return ev;
}

bool event_queue_empty() {
    return priority_queue_empty(event_queue);
}

bool timer_is_running_A(void *a, void *b) {
    const Event *event_a = a;
    return event_a->sdt == A && event_a->type == TIMER_INTERUPT;
}

bool timer_is_running_B(void *a, void *b) {
    const Event *event_a = a;
    return event_a->sdt == B && event_a->type == TIMER_INTERUPT;
}

bool has_timeout_event(side s) {
    if (s == A) {
        return priority_queue_has_element(event_queue, timer_is_running_A, NULL);
    } else {
        return priority_queue_has_element(event_queue, timer_is_running_B, NULL);
    }
}

void remove_timeout_event(side s) {
    if (s == A) {
        priority_queue_remove_element(event_queue, timer_is_running_A, NULL);
    } else {
        priority_queue_remove_element(event_queue, timer_is_running_B, NULL);
    }
}