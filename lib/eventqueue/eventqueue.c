#include "eventqueue/eventqueue.h"

static PriorityQueue *event_queue = NULL;

void free_event(void *event) {
	free(((Event *)event)->data);
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

void eventqueue_destroy() {
	priority_queue_free(event_queue, free_event);
	event_queue = NULL;
}


void new_from_layer5_event(double delay, side sdt, void *data) {
    Event *event = malloc(sizeof(Event));
    event->type = FROM_LAYER5;
    event->activation_time = delay + get_time();
    event->sdt = sdt;
    event->data = data;
	priority_queue_push(event_queue, event);
}

void new_from_layer3_event(double delay, side sdt, void *data) {
    Event *event = malloc(sizeof(Event));
    event->type = FROM_LAYER3;
    event->activation_time = delay + get_time();
    event->sdt = sdt;
    event->data = data;
	priority_queue_push(event_queue, event);
}

void new_timeout_event(double delay, side sdt) {
    Event *event = malloc(sizeof(Event));
    event->type = TIMEOUT_EVENT;
    event->activation_time = delay + get_time();
    event->sdt = sdt;
    event->data = NULL;
	priority_queue_push(event_queue, event);
}

void new_to_layer5_event(double delay, side sdt, void *data) {
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
        case TIMEOUT_EVENT:
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
    printf("(%c) at %f\n", sendto_to_char(e->sdt), e->activation_time);
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