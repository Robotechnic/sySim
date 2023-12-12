#include "softwareinterface/softwareinterface.h"

#define RANDINT(x) (rand() % x)
#define RANDRANGE(x, y) (rand() % (y - x) + x)

static float corruption = 0.0;
static float loss = 0.0;
static side current_side = A;

bool random_less_than(float p) {
    return (float)rand() / (float)RAND_MAX < p;
}

void corrupt(Packet *packet) {
    size_t size = packet->size;
    unsigned char *data = (unsigned char *)packet;
    int num_corrupt = RANDINT(5);
    for (int i = 0; i < num_corrupt; i++) {
        int index = RANDINT(size);
        data[index] = (unsigned char)RANDINT(256);
    }
}

void stoptimer() {
    if (has_timeout_event(current_side)) {
        log_trace("Timer %c stopped", side_to_char(current_side));
        remove_timeout_event(current_side);
    } else {
        log_error("Timer %c not running", side_to_char(current_side));
    }
}

void starttimer(double increment) {
    if (has_timeout_event(current_side)) {
        log_error("Timer %c already running", side_to_char(current_side));
    } else {
        log_trace("Timer %c started", side_to_char(current_side));
        new_timeout_event(increment, current_side);
    }
}

void tolayer3(Packet *packet) {
    if (random_less_than(loss)) {
        log_debug("PACKET BEING LOST");
        return;
    }
    if (random_less_than(corruption)) {
        log_debug("PACKET BEING CORRUPTED");
        corrupt(packet);
    }
    new_from_layer3_event(5 + RANDRANGE(-2, 10), current_side == A ? B : A, packet);
}

void tolayer5(const Payload *message) {
    Payload data;
    memcpy(data.data, message->data, PAYLOAD_SIZE);
    new_to_layer5_event(0, current_side, data);
}

void set_layer3_corruption(float c) {
    corruption = c;
}

void set_layer3_loss(float l) {
    loss = l;
}

void set_side(side s) {
    current_side = s;
}