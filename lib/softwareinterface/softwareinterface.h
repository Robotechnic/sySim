#ifndef SOFTWAREINTERFACE_H
#define SOFTWAREINTERFACE_H

#include "eventqueue/eventqueue.h"
#include "protocol/protocol.h"
#include "package/package.h"

void stoptimer(side s);

void starttimer(side s, double increment);

void tolayer3(side s, Packet *packet);

void tolayer5(side s, Payload *message);

void set_layer3_corruption(float c);
void set_layer3_loss(float l);

#endif // SOFTWAREINTERFACE_H