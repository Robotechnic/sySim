#include "protocol/protocol.h"
#include <assert.h>

DEFINE_PACKET(WrongOrderPacket, int test;)

typedef struct bucket {
    WrongOrderPacket *packet;
    struct bucket *next;
    struct bucket *prev;
} Bucket;

Bucket *initBucket() {
    Bucket *bucket = malloc(sizeof(Bucket));
    bucket->next = bucket;
    bucket->prev = bucket;
    bucket->packet = NULL;
    return bucket;
}

void insert(Bucket *bucket, WrongOrderPacket *packet) {
    if (bucket->packet == NULL) {
        bucket->packet = packet;
        return;
    }
    Bucket *new = malloc(sizeof(Bucket));
    new->packet = packet;
    new->next = bucket->next;
    new->prev = bucket;
    bucket->next->prev = new;
    bucket->next = new;
}

void drop(Bucket *bucket) {
    if (bucket->packet == NULL) {
        return;
    }
    if (bucket->next == bucket) {
        return;
    }
    bucket->prev->next = bucket->next;
    bucket->next->prev = bucket->prev;
    free(bucket);
}

typedef struct wrongOrderState {
    size_t messages;
    Bucket *packets;
} WrongOrderState;

void *A_init() {
    WrongOrderState *s = malloc(sizeof(WrongOrderState));
    s->messages = 0;
    s->packets = initBucket();
    return s;
}

void *B_init() {
    return A_init();
}

void A_send(void *state, Payload payload) {
    WrongOrderState *s = state;
    WrongOrderPacket *packet = WrongOrderPacket_new(&payload);
    packet->test = 0;
    insert(s->packets, packet);
    s->messages++;
    if (s->messages > 1) {
        stoptimer();
    }
    starttimer(30);
}

void B_send(void *state, Payload payload) {
    A_send(state, payload);
}

void A_recv(void *state, const Packet *packet) {
    (void)state;
    tolayer5(&packet->payload);
}

void B_recv(void *state, const Packet *packet) {
    A_recv(state, packet);
}

void A_timer_interrupt(void *state) {
    WrongOrderState *s = state;
    while (s->messages > 0) {
        tolayer3((Packet *)s->packets->packet);
        s->packets = s->packets->next;
        drop(s->packets->prev);
        s->messages--;
    }
}

void B_timer_interrupt(void *state) {
    A_timer_interrupt(state);
}

void A_free(void *state) {
    WrongOrderState *s = state;
    while (s->messages > 0) {
        free(s->packets->packet);
        s->packets = s->packets->next;
        drop(s->packets->prev);
        s->messages--;
    }

    free(s->packets);
    free(state);
}

void B_free(void *state) {
    A_free(state);
}
