#include "simulator/simulator.h"

typedef struct event {
	enum {
		TIMEOUT_EVENT,
		SEND_EVENT,
		RECEIVE_EVENT
	} type;
	double activation_time;
	sendto sdt;
	void *data;
} Event;

bool compare_event(void *a, void *b) {
	Event *event_a = (Event *) a;
	Event *event_b = (Event *) b;
	return event_a->activation_time < event_b->activation_time;
}

Event *send_event(double activation_time, sendto sdt, void *data) {
	Event *event = malloc(sizeof(Event));
	event->type = SEND_EVENT;
	event->activation_time = activation_time;
	event->sdt = sdt;
	event->data = data;
	return event;
}

Event *receive_event(double activation_time, sendto sdt, void *data) {
	Event *event = malloc(sizeof(Event));
	event->type = RECEIVE_EVENT;
	event->activation_time = activation_time;
	event->sdt = sdt;
	event->data = data;
	return event;
}

Event *timeout_event(double activation_time, sendto sdt) {
	Event *event = malloc(sizeof(Event));
	event->type = TIMEOUT_EVENT;
	event->activation_time = activation_time;
	event->sdt = sdt;
	event->data = NULL;
	return event;
}

void print_event(void *event) {
	const Event *e = (Event *) event;
	switch (e->type) {
		case TIMEOUT_EVENT:
			printf("TIMEOUT_EVENT ");
			break;
		case SEND_EVENT:
			printf("SEND_EVENT    ");
			break;
		case RECEIVE_EVENT:
			printf("RECEIVE_EVENT ");
			break;
	}
	printf("(%c) at %f\n", sendto_to_char(e->sdt), e->activation_time);
}

void run_simulation(int messages, float corruption, float loss, float delay, int seed) {
    srand(seed);
    (void) messages;
	(void) corruption;
	(void) loss;
	(void) delay;

	double tick = 0;
	
	PriorityQueue *event_queue = priority_queue_new(compare_event, 10);
	sendto sdt = A;
	for (int i = 0; i < messages; i++) {
		priority_queue_push(event_queue, send_event(i * delay, sdt, NULL));
		sdt = (sdt == A) ? B : A;
	}

	void *A_state = A_init();
	void *B_state = B_init();
	Event *event = NULL;

	while (!priority_queue_empty(event_queue)) {
		event = priority_queue_pop(event_queue);
		if (event->activation_time > tick) {
			tick = event->activation_time;
		}
		switch (event->type) {
			case TIMEOUT_EVENT:
				if (event->sdt == A) {
					A_timeout(A_state);
				} else {
					B_timeout(B_state);
				}
				break;
			case SEND_EVENT:
				if (event->sdt == A) {
					A_send(A_state, event->data);
				} else {
					B_send(B_state, event->data);
				}
				break;
			case RECEIVE_EVENT:
				if (event->sdt == A) {
					A_recv(A_state, event->data);
				} else {
					B_recv(B_state, event->data);
				}
				break;
		}
		free(event);
	}

	A_free(A_state);
	B_free(B_state);
}