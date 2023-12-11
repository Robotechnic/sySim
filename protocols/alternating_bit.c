#include "protocol/protocol.h"

DEFINE_PACKAGE(
	OneBitProtocol,
	{
		int acknum;
		int seqnum;
	}
)

#define SEND_TIMEOUT 20.0

typedef struct state_t {
    int id;
    int seqnum;
    int acknum;
    bool waiting_ack;
    Package *current_packet;
} State;

void *A_init() {
	State *state = malloc(sizeof(State));
	state->id = 0;
	state->seqnum = 0;
	state->acknum = 0;
	state->waiting_ack = false;
	state->current_packet = NULL;
	return state;
}

void *B_init() {
	return A_init();
}


void A_send(void *state, Payload *payload) {
	(void) payload;
	(void) state;
}

void B_send(void *state, Payload *payload) {
	(void) payload;
	(void) state;
}

void A_recv(void *state, Package *packet) {
    (void) packet;
    (void) state;
}

void B_recv(void *state, Package *packet) {
    (void) packet;
    (void) state;
}

void A_timeout(void *state) {
	(void) state;
}

void B_timeout(void *state) {
	(void) state;
}

void A_free(void *state) {
	free(state);
}

void B_free(void *state) {
	free(state);
}
