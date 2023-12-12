#include "simulator/simulator.h"

void run_simulation(size_t messages, float corruption, float loss, float delay, int seed,
                    bool bidirectional, double max_time) {
    srand(seed);

    log_debug("Running simulation with:");
    log_debug("\tMessages:   %zu", messages);
    log_debug("\tCorruption: %.2f", corruption);
    log_debug("\tLoss:       %.2f", loss);
    log_debug("\tDelay:      %.2fs", delay);
    log_debug("\tSeed:       %d", seed);

    reset_time();
    eventqueue_init(messages * 3);
    set_layer3_loss(loss);
    set_layer3_corruption(corruption);

    side sdt = A;
    for (unsigned i = 0; i < messages; i++) {
        char message[20];
        snprintf(message, 20, "%d", i);
        Payload payload = payload_new(message);
        new_from_layer5_event((float)i * delay, sdt, payload);
        if (bidirectional) {
            sdt = (sdt == A) ? B : A;
        }
    }

    void *A_state = A_init();
    void *B_state = B_init();
    Event *event = NULL;

    while (!event_queue_empty() && get_time() < max_time) {
        event = event_queue_pop_event();
        switch (event->type) {
            case TIMER_INTERUPT:
                log_trace("TIMER_INTERUPT <- %c", side_to_char(event->sdt));
                if (event->sdt == A) {
                    A_timer_inerrupt(A_state);
                } else {
                    B_timer_interrupt(B_state);
                }
                break;
            case FROM_LAYER5:
                log_trace("FROM_LAYER5 -> %c", side_to_char(event->sdt));
                if (event->sdt == A) {
                    A_send(A_state, event->data);
                } else {
                    B_send(B_state, event->data);
                }
                break;
            case FROM_LAYER3:
                log_trace("FROM_LAYER3 <- %c", side_to_char(event->sdt));
                if (event->sdt == A) {
                    A_recv(A_state, event->any);
                } else {
                    B_recv(B_state, event->any);
                }
                break;
            case TO_LAYER_5:
                log_trace("TO_LAYER_5 -> %c", side_to_char(event->sdt));
                log_debug("SIDE '%c' NOTIFIED A NEW MESSAGE: \"%.*s\"", side_to_char(event->sdt),
                          20, event->data.data);

                break;
        }
        free(event);
    }

    if (get_time() >= max_time) {
        log_error("Simulation timed out");
    }

    A_free(A_state);
    B_free(B_state);
    eventqueue_free();
}