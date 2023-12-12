#include "softwareinterface/softwareinterface.h"

#define RANDINT(x) (rand() % x)

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
		log_trace("Timer %s stopped", sendto_to_char(s));
		remove_timeout_event(s);
	} else {
    	log_error("Timer %s not running", sendto_to_char(s));
	}
}

void starttimer(side s, double increment) {
	if (has_timeout_event(s)) {
		log_error("Timer %s already running", sendto_to_char(s));
	} else {
		log_trace("Timer %s started", sendto_to_char(s));
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
	new_from_layer3_event(10.0, s, packet);
}

void tolayer5(side s, Payload *message) {
	new_from_layer5_event(10.0, s, message);
}

void set_layer3_corruption(float c) {
	corruption = c;
}

void set_layer3_loss(float l) {
	loss = l;
}