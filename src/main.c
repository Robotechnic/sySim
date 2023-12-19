#include "argparse/argparse.h"
#include "logger/log.h"
#include "simulator/simulator.h"
#include <stdio.h>
#include <stdlib.h>

bool check_args(struct gengetopt_args_info *args_info, FILE *log_file) {
    if (args_info->loglevel_arg < 0 || args_info->loglevel_arg > 4) {
        fprintf(stderr, "Log level must be between 0 and 4\n");
        return false;
    }

    if (args_info->logfile_given) {
        log_file = fopen(args_info->logfile_arg, "w");
        if (log_file == NULL) {
            fprintf(stderr, "Error opening log file %s\n", args_info->logfile_arg);
            return false;
        }
    }

    if (args_info->messages_arg < 1) {
        fprintf(stderr, "Number of messages must be at least 1\n");
        return false;
    }

    if (args_info->maxTime_arg < 0) {
        fprintf(stderr, "Max time must be at least 0\n");
        return false;
    }

    return true;
}

int main(int argc, char **argv) {
    argc = 4;
    argv[1] = "-L";
    argv[2] = "0";
    argv[3] = "-C";

    struct gengetopt_args_info args_info;

    if (cmdline_parser(argc, argv, &args_info) != 0) {
        exit(1);
    }

    FILE *log_file = NULL;
    if (!check_args(&args_info, log_file)) {
        cmdline_parser_free(&args_info);
        exit(1);
    }

    log_set_level(args_info.loglevel_arg);
    log_set_quiet(args_info.quiet_flag);
    log_set_color(args_info.color_flag);

    SimulationConfig config = {.messages = args_info.messages_arg,
                               .corruption = args_info.corruption_arg,
                               .bidirectional = args_info.bidirectional_flag,
                               .loss = args_info.loss_arg,
                               .delay = args_info.delay_arg,
                               .max_time = args_info.maxTime_arg,
                               .seed = args_info.seed_arg,
                               .check = args_info.check_flag};

    run_simulation(&config);

    if (log_file != NULL) {
        fclose(log_file);
    }
    cmdline_parser_free(&args_info);
    return 0;
}
