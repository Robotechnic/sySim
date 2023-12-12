#include "softwareinterface/softwareinterface.h"

#define RANDINT(x) (rand() % x)
#define RANDRANGE(x, y) (rand() % (y - x) + x)

static float corruption = 0.0;
static float loss = 0.0;

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

void stoptimer(side s) {
    if (has_timeout_event(s)) {
		log_trace("Timer %s stopped", side_to_char(s));
		remove_timeout_event(s);
	} else {
    	log_error("Timer %s not running", side_to_char(s));
	}
}

void starttimer(side s, double increment) {
	if (has_timeout_event(s)) {
		log_error("Timer %c already running", side_to_char(s));
	} else {
		log_trace("Timer %c started", side_to_char(s));
		new_timeout_event(increment, s);
	}
}

void tolayer3(side s, Packet *packet) {
	if (random_less_than(loss)) {
		log_debug("PACKET BEING LOST");
		return;
	}
	if (random_less_than(corruption)) {
		log_debug("PACKET BEING CORRUPTED");
		corrupt(packet);
	}
    new_from_layer3_event(5 + RANDRANGE(-2,10), s, packet);
}

void tolayer5(side s, const Payload *message) {
    log("============= %c: message received =============\n", side_to_char(s));
    log("%.*s\n", 20, message->data);
    log("================================================\n");
	char *data = malloc(PAYLOAD_SIZE + 1);
	memcpy(data, message->data, PAYLOAD_SIZE);
	data[PAYLOAD_SIZE] = '\0';
    new_from_layer5_event(0, s, data);
}

void set_layer3_corruption(float c) {
	corruption = c;
}

void set_layer3_loss(float l) {
	loss = l;
}