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
        snprintf(message, 20, "%d", i);
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

void run_simulation(const SimulationConfig *config) {

    init_simulation(config);

    void *A_state = A_init();
    void *B_state = B_init();
    Event *event = NULL;

    while (!event_queue_empty() && get_time() < config->max_time) {
        event = event_queue_pop_event();
        switch (event->type) {
            case TIMER_INTERUPT:
                log_trace("TIMER_INTERUPT <- %c", side_to_char(event->sdt));
                set_side(event->sdt);
                if (event->sdt == A) {
                    A_timer_inerrupt(A_state);
                } else {
                    B_timer_interrupt(B_state);
                }
                break;
            case FROM_LAYER5:
                log_trace("FROM_LAYER5 -> %c", side_to_char(event->sdt));
                set_side(event->sdt);
                if (event->sdt == A) {
                    A_send(A_state, event->data);
                } else {
                    B_send(B_state, event->data);
                }
                break;
            case FROM_LAYER3:
                log_trace("FROM_LAYER3 <- %c", side_to_char(event->sdt));
                set_side(event->sdt);
                if (event->sdt == A) {
                    A_recv(A_state, event->packet);
                } else {
                    B_recv(B_state, event->packet);
                }
                free(event->packet);
                break;
            case TO_LAYER_5:
                log_trace("TO_LAYER_5 -> %c", side_to_char(event->sdt));
                log_debug("SIDE '%c' NOTIFIED A NEW MESSAGE: \"%.*s\"", side_to_char(event->sdt),
                          20, event->data.data);

                break;
        }
        free(event);
    }

    if (get_time() >= config->max_time) {
        log_error("Simulation timed out");
    }

    A_free(A_state);
    B_free(B_state);
    eventqueue_free();
}