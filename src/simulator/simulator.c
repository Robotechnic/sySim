#include "simulator/simulator.h"

void init_simulation(const SimulationConfig *config) {
    srand(config->seed);

    reset_time();
    eventqueue_init(config->messages * 3);
    set_layer3_loss(config->loss);
    set_layer3_corruption(config->corruption);

    side sdt = A;
    for (unsigned i = 0; i < config->messages; i++) {
        char message[20];
        snprintf(message, 20, "Payload(%d)", i);
        Payload payload = payload_new(message);
        new_from_layer5_event((float)i * config->delay, sdt, payload);
        if (config->bidirectional) {
            sdt = (sdt == A) ? B : A;
        }
    }

    log_debug("Running simulation with:");
    log_debug("\tMessages:      %zu", config->messages);
    log_debug("\tCorruption:    %.2f", config->corruption);
    log_debug("\tLoss:          %.2f", config->loss);
    log_debug("\tDelay:         %.2fs", config->delay);
    log_debug("\tSeed:          %d", config->seed);
    log_debug("\tBidirectional: %s", config->bidirectional ? "true" : "false");
}

/**
 * @brief Run the timer interrupt for the given side
 *
 * @param event the timer interrupt event to handle
 * @param A_state the A side internal state
 * @param B_state the B side internal state
 */
void simulator_timer_interrupt(const Event *event, void *A_state, void *B_state) {
    log_trace("TIMER_INTERUPT <- %c", side_to_char(event->sdt));
    set_side(event->sdt);
    if (event->sdt == A) {
        A_timer_inerrupt(A_state);
    } else {
        B_timer_interrupt(B_state);
    }
}

/**
 * @brief run the send function for the given side
 *
 * @param event the from layer 5 event to handle
 * @param A_state the A side internal state
 * @param B_state the B side internal state
 * @param check true if the simulator should save the message for later checking
 * @param A_messages the queue of messages sent by A
 * @param B_messages the queue of messages sent by B
 */
void simulator_from_layer5(const Event *event, void *A_state, void *B_state, bool check,
                           Queue *A_messages, Queue *B_messages) {
    log_trace("FROM_LAYER5 -> %c", side_to_char(event->sdt));
    set_side(event->sdt);
    if (event->sdt == A) {
        A_send(A_state, event->data);
    } else {
        B_send(B_state, event->data);
    }
    if (!check) {
        return;
    }
    assert(A_messages != NULL);
    assert(B_messages != NULL);
    char *data = malloc(PAYLOAD_SIZE);
    strncpy(data, event->data.data, PAYLOAD_SIZE);
    if (event->sdt == B) {
        queue_push(A_messages, data);
    } else {
        queue_push(B_messages, data);
    }
}

/**
 * @brief run the receive function for the given side
 *
 * @param event the from layer 3 event to handle
 * @param A_state the A side internal state
 * @param B_state the B side internal state
 */
void simulator_from_layer3(const Event *event, void *A_state, void *B_state) {
    log_trace("FROM_LAYER3 <- %c", side_to_char(event->sdt));
    set_side(event->sdt);
    if (event->sdt == A) {
        A_recv(A_state, event->packet);
    } else {
        B_recv(B_state, event->packet);
    }
    free(event->packet);
}

/**
 * @brief Check if the message received is the same as the one sent
 *
 * @param event the to layer 5 event to handle
 * @param check if the simulator should check the message
 * @param A_messages the queue of messages sent by A
 * @param B_messages the queue of messages sent by B
 * @return true if the message received is not the right one
 */
bool simulator_to_layer5(const Event *event, bool check, Queue *A_messages, Queue *B_messages) {
    log_trace("TO_LAYER_5 -> %c", side_to_char(event->sdt));
    log_debug("SIDE '%c' NOTIFIED A NEW MESSAGE: \"%.*s\"", side_to_char(event->sdt), 20,
              event->data.data);
    if (!check) {
        return false;
    }
    char *data;
    if (event->sdt == A) {
        data = queue_pop(A_messages);
    } else {
        data = queue_pop(B_messages);
    }
    if (strncmp(data, event->data.data, PAYLOAD_SIZE) != 0) {
        log_error("SIDE '%c' RECEIVED THE WRONG MESSAGE: \"%.*s\"", side_to_char(event->sdt), 20,
                  event->data.data);
        free(data);
        return true;
    }
    log_debug("SIDE '%c' RECEIVED THE RIGHT MESSAGE", side_to_char(event->sdt));
    free(data);
    return false;
}

bool run_simulation(const SimulationConfig *config) {

    init_simulation(config);

    void *A_state = A_init();
    void *B_state = B_init();
    Event *event = NULL;

    Queue *A_messages = NULL;
    Queue *B_messages = NULL;

    if (config->check) {
        A_messages = queue_new(5);
        B_messages = queue_new(5);
    }

    bool error = false;

    while (!event_queue_empty() && get_time() < config->max_time && !error) {
        event = event_queue_pop_event();
        switch (event->type) {
            case TIMER_INTERUPT:
                simulator_timer_interrupt(event, A_state, B_state);
                break;
            case FROM_LAYER5:
                simulator_from_layer5(event, A_state, B_state, config->check, A_messages,
                                      B_messages);
                break;
            case FROM_LAYER3:
                simulator_from_layer3(event, A_state, B_state);
                break;
            case TO_LAYER_5:
                error = simulator_to_layer5(event, config->check, A_messages, B_messages);
                break;
        }
        free(event);
    }

    if (get_time() >= config->max_time) {
        log_error("Simulation timed out");
    }

    if (config->check) {
        queue_free(A_messages, free);
        queue_free(B_messages, free);
    }

    A_free(A_state);
    B_free(B_state);
    eventqueue_free();

	return error;
}