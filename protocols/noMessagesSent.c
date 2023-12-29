#include "protocol/protocol.h"

DEFINE_PACKET(TestPacket, )

typedef struct test_state {
    int test;
} TestState;

void *A_init() {
    TestState *s = malloc(sizeof(TestState));
    return s;
}

void *B_init() {
    TestState *s = malloc(sizeof(TestState));
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
    log_error("A_recv function should never be called");
    (void)state;
    (void)packet;
}

void B_recv(void *state, const Packet *packet) {
    log_error("B_recv function should never be called");
    (void)state;
    (void)packet;
}

void A_timer_interrupt(void *state) {
    log_error("A_timer_interrupt function should never be called");
    (void)state;
}

void B_timer_interrupt(void *state) {
    log_error("B_timer_interrupt function should never be called");
    (void)state;
}

void A_free(void *state) {
    free(state);
}

void B_free(void *state) {
    free(state);
}
