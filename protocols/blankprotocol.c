#include "protocol/protocol.h"

DEFINE_PACKET(BlankPacket, int test;)

typedef struct blankState {
    int test;
} BlankState;

void *A_init() {
    BlankState *s = malloc(sizeof(BlankState));
    return s;
}

void *B_init() {
    BlankState *s = malloc(sizeof(BlankState));
    return s;
}

void A_send(void *state, Payload payload) {
    (void)state;
    (void)payload;
}

void B_send(void *state, Payload payload) {
    (void)state;
    (void)payload;
}

void A_recv(void *state, const Packet *packet) {
    (void)state;
    (void)packet;
}

void B_recv(void *state, const Packet *packet) {
    (void)state;
    (void)packet;
}

void A_timer_inerrupt(void *state) {
    (void)state;
}

void B_timer_interrupt(void *state) {
    (void)state;
}

void A_free(void *state) {
    free(state);
}

void B_free(void *state) {
    free(state);
}
