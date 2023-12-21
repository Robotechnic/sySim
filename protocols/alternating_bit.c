#include "protocol/protocol.h"

DEFINE_PACKET(OneBitPackage, int checksum; int acknum; int seqnum;)

#define SEND_TIMEOUT 25.0

typedef struct state_t {
    side id;
    int seqnum;
    int acknum;
    bool waiting_ack;
    Queue *message_queue;
    OneBitPackage *current_packet;
} State;

void printBits(size_t const size, void const *const ptr) {
    const unsigned char *b = (const unsigned char *)ptr;
    unsigned char byte;

    for (ssize_t i = size - 1; i >= 0; i--) {
        for (int j = 7; j >= 0; j--) {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    printf("\n");
}

/**
 * @brief Compute the 16-bit checksum of a byte sequence
 *
 * @param data the pointer to the structure wich contains the checksum
 * @param n the struct size
 * @return int the checksum to put in a int field
 */
int checksum(const void *data, size_t n) {
    const unsigned char *bits = (const unsigned char *)data;
    unsigned sum = 0;
    for (size_t i = 0; i < n; i += 2) {
        unsigned trame = 0;
        trame = (bits[i]) | ((bits[i + 1] << 8) & 0xff00);
        sum += trame;
    }
    sum %= 0xffff;
    sum = 0xffff - sum;
    return sum;
}

/**
 * @brief check if a packet is corrupted
 *
 * @param packet the packet to check
 * @return true if the packet is corrupted
 */
bool is_corrupted(const OneBitPackage *packet) {
    int check = checksum(packet, sizeof(OneBitPackage)) ^ 0xffff;
    return check != 0;
}

/**
 * @brief Build a packet with the right sequence number and checksum
 *
 * @param acknum the ack number
 * @param seqnum the sequence number
 * @param message the message to put in the packet
 * @return pkt_t the new packet
 */
OneBitPackage *create_packet(int acknum, int seqnum, Payload message) {
    OneBitPackage *packet = OneBitPackage_new(&message);
    packet->acknum = acknum;
    packet->seqnum = seqnum;
    packet->checksum = 0;
    packet->checksum = checksum(packet, sizeof(OneBitPackage));
    return packet;
}

/**
 * @brief Compute the next sequence number
 *
 * @param seqnum the current sequence number
 * @return int the next sequence number
 */
int next_seqnum(int seqnum) {
    return (seqnum + 1) % 2;
}

/**
 * @brief Send the given message to the other host
 *
 * @param state the current host state
 * @param message the message to send
 */
void output(State *state, Payload message) {
    if (state->waiting_ack) {
        int seq = next_seqnum(state->seqnum);
        if (queue_size(state->message_queue) > 0) {
            seq = next_seqnum(((OneBitPackage *)queue_back(state->message_queue))->seqnum);
        }
        log("%c: packet %d is waiting for ack, queueing packet with seqnum %d",
            side_to_char(state->id), state->seqnum, seq);
        OneBitPackage *packet = create_packet(-1, seq, message);
        queue_push(state->message_queue, packet);
        return;
    }
    log("%c: sending packet %d", side_to_char(state->id), state->seqnum);
    OneBitPackage *packet = create_packet(-1, state->seqnum, message);
    state->waiting_ack = true;
    state->current_packet = packet;
    tolayer3(OneBitPackage_dup(packet));
    starttimer(SEND_TIMEOUT);
}

/**
 * @brief Manages the timeout of a packet and resend it if needed
 *
 * @param state the current host state
 */
void timer_interrupt(State *state) {
    if (!state->waiting_ack) {
        return;
    }
    log("%c: timeout, resending packet %d", side_to_char(state->id), state->seqnum);
    tolayer3(OneBitPackage_dup(state->current_packet));
    starttimer(SEND_TIMEOUT);
}

/**
 * @brief Analyse the output of the other host and send an ack if needed
 *
 * @param state the curent host state
 * @param packet the packet received
 */
void input(State *state, const Packet *p) {
    const OneBitPackage *packet = (const OneBitPackage *)p;
    if (is_corrupted(packet)) {
        log("%c: corrupted packet received", side_to_char(state->id));
        return;
    }
    log("%c: new packet received", side_to_char(state->id));
    log("%c: ack number: %d", side_to_char(state->id), packet->acknum);
    log("%c: seq number: %d", side_to_char(state->id), packet->seqnum);
    if (packet->acknum == state->seqnum) {
        log("%c: ack number is correct", side_to_char(state->id));
        stoptimer(state->id);
        state->seqnum = next_seqnum(state->seqnum);
        free(state->current_packet);
        if (queue_empty(state->message_queue)) {
            state->waiting_ack = false;
            state->current_packet = NULL;
        } else {
            state->current_packet = queue_pop(state->message_queue);
            log("%c: sending queued packet %d", side_to_char(state->id),
                state->current_packet->seqnum);
            tolayer3(OneBitPackage_dup(state->current_packet));
            starttimer(SEND_TIMEOUT);
        }
    } else if (packet->acknum != -1) {
        log_error("%c: ack number is wrong", side_to_char(state->id));
    }

    if (packet->seqnum == -1) {
        return;
    }

    if (packet->seqnum == state->acknum) {
        tolayer5(&packet->payload);
        state->acknum = next_seqnum(state->acknum);
    } else {
        log("%c: wrong seq number received", side_to_char(state->id));
    }

    OneBitPackage *ack = create_packet(packet->seqnum, -1, enpty_payload());
    log("%c: sending back ack %d", side_to_char(state->id), packet->seqnum);
    tolayer3((Packet *)ack);
}

void *A_init() {
    State *state = malloc(sizeof(State));
    state->id = A;
    state->seqnum = 0;
    state->acknum = 0;
    state->waiting_ack = false;
    state->current_packet = NULL;
    state->message_queue = queue_new(5);
    return state;
}

void *B_init() {
    State *state = A_init();
    state->id = B;
    return state;
}

void A_send(void *state, Payload payload) {
    output(state, payload);
}

void B_send(void *state, Payload payload) {
    output(state, payload);
}

void A_recv(void *state, const Packet *packet) {
    input(state, packet);
}

void B_recv(void *state, const Packet *packet) {
    input(state, packet);
}

void A_timer_interrupt(void *state) {
    timer_interrupt(state);
}

void B_timer_interrupt(void *state) {
    timer_interrupt(state);
}

void pf(void *state) {
    package_free(state);
}

void A_free(void *state) {
    State *s = (State *)state;
    queue_free(s->message_queue, pf);
    package_free((Packet *)s->current_packet);
    free(state);
}

void B_free(void *state) {
    A_free(state);
}
