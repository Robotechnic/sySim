#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "logger/log.h"
#include "package/package.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef enum sendto_e { A, B } sendto_t;

/**
 * @brief This function is called once at the beginning of the simulation.
 *
 * @return void* the A current state
 */
void *A_init();

/**
 * @brief This function is called once at the beginning of the simulation.
 *
 * @return void* the B current state
 */
void *B_init();

/**
 * @brief This function is called when the simulation wants to send a payload to the other side.
 *
 * @param state the current state
 * @param payload the payload to send
 */
void A_send(void *state, Payload *payload);

/**
 * @brief This function is called when the simulation wants to send a payload to the other side.
 *
 * @param state the current state
 * @param payload the payload to send
 */
void B_send(void *state, Payload *payload);

/**
 * @brief This function is called when the simulation receives a packet from the other side.
 *
 * @param state the current state
 * @param packet the received packet
 */
void A_recv(void *state, Package *packet);

/**
 * @brief This function is called when the simulation receives a packet from the other side.
 *
 * @param state the current state
 * @param packet the received packet
 */
void B_recv(void *state, Package *packet);

/**
 * @brief This function is called when the timeout of the A side is reached.
 *
 * @param state the current state
 */
void A_timeout(void *state);

/**
 * @brief This function is called when the timeout of the B side is reached.
 *
 * @param state the current state
 */
void B_timeout(void *state);

/**
 * @brief This function is called when the simulation is over.
 *
 * @param state the current state
 */
void A_destroy(void *state);

/**
 * @brief This function is called when the simulation is over.
 *
 * @param state the current state
 */
void B_destroy(void *state);

#endif // PROTOCOL_H