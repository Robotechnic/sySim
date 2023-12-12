#ifndef SOFTWAREINTERFACE_H
#define SOFTWAREINTERFACE_H

#include "eventqueue/eventqueue.h"
#include "package/package.h"
#include "protocol/protocol.h"

void stoptimer();

void starttimer(double increment);

void tolayer3(Packet *packet);

void tolayer5(const Payload *message);

void set_layer3_corruption(float c);
void set_layer3_loss(float l);
void set_side(side s);

#endif // SOFTWAREINTERFACE_H