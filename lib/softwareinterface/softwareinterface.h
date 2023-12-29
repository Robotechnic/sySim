#ifndef SOFTWAREINTERFACE_H
#define SOFTWAREINTERFACE_H

#include "eventqueue/eventqueue.h"
#include "package/package.h"
#include "protocol/protocol.h"

/**
 * @brief Delete the timer that is currently running for the current side.
 *
 */
void stoptimer();

/**
 * @brief Start a timer for the current side.
 *
 * @param increment The amount of time to wait before the timer expires.
 */
void starttimer(double increment);

/**
 * @brief Send a packet to the other side.
 *
 * @param packet The packet to send.
 */
void tolayer3(Packet *packet);

/**
 * @brief Send a message to the application layer. This function is used by the
 * simulator to check if the message was received correctly.
 *
 * @param message The message to send.
 */
void tolayer5(const Payload *message);

void set_layer3_corruption(float c);
void set_layer3_loss(float l);
void set_side(side s);

#endif // SOFTWAREINTERFACE_H