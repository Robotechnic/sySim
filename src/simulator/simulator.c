#include "simulator/simulator.h"

void run_simulation(size_t messages, float corruption, float loss, float delay, int seed, bool bidirectional) {
    srand(seed);
    (void) messages;
	(void) corruption;
	(void) loss;

	reset_time();
	eventqueue_init(messages * 3);

	side sdt = A;
	for (unsigned i = 0; i < messages; i++) {
		char message[20];
		snprintf(message, 20, "%d", i);
		new_from_layer5_event((float)i * delay, sdt, payload_new(message));
		if (bidirectional) {
			sdt = (sdt == A) ? B : A;
		}
	}

	void *A_state = A_init();
	void *B_state = B_init();
	Event *event = NULL;

    while (!event_queue_empty()) {
        event = event_queue_pop_event();
		switch (event->type) {
			case TIMEOUT_EVENT:
				log_trace("TIMEOUT_EVENT <- %s", sendto_to_char(event->sdt));
				if (event->sdt == A) {
					A_timeout(A_state);
				} else {
					B_timeout(B_state);
				}
				break;
			case FROM_LAYER5:
				log_trace("FROM_LAYER5 -> %s", sendto_to_char(event->sdt));
				if (event->sdt == A) {
					A_send(A_state, event->data);
				} else {
					B_send(B_state, event->data);
				}
				break;
			case FROM_LAYER3:
				log_trace("FROM_LAYER3 <- %s", sendto_to_char(event->sdt));
				if (event->sdt == A) {
					A_recv(A_state, event->data);
				} else {
					B_recv(B_state, event->data);
				}
				payload_free(event->data);
				break;
			case TO_LAYER_5:
				log_trace("TO_LAYER_5 -> %s", sendto_to_char(event->sdt));
				log_trace("\tMessage: %s", (char *)event->data);
				break;
		}
		free(event);
    }

    A_free(A_state);
	B_free(B_state);
}