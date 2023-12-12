#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "logger/log.h"
#include "package/package.h"
#include "eventqueue/eventqueue.h"
#include "protocol/protocol.h"
#include "softwareinterface/softwareinterface.h"
#include "time/time.h"
#include <stdlib.h>

/**
 * @brief Run a new simulation on the given parameters. It uses the function that defines the
 * protocol in protocols
 *
 * @param messages the number of messages to be sent
 * @param corruption the probability of a package being corrupted
 * @param loss the probability of a package being lost
 * @param delay the mean delay to send a package
 * @param seed the random seed
 */
void run_simulation(size_t messages, float corruption, float loss, float delay, int seed, bool bidirectional);

#endif // SIMULATOR_H