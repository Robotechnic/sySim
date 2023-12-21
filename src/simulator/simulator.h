#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "eventqueue/eventqueue.h"
#include "logger/log.h"
#include "package/package.h"
#include "protocol/protocol.h"
#include "softwareinterface/softwareinterface.h"
#include "time/time.h"
#include <assert.h>
#include <stdlib.h>

typedef struct simulation_config {
    size_t messages;
    float corruption;
    float loss;
    float delay;
    int seed;
    bool bidirectional;
    double max_time;
    bool check;
	bool ignore_failure;
} SimulationConfig;

/**
 * @brief Run a new simulation on the given parameters. It uses the function that defines the
 * protocol in protocols
 *
 * @param config The configuration of the simulation
 */
bool run_simulation(const SimulationConfig *config);

#endif // SIMULATOR_H