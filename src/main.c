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

    return true;
}

int main(int argc, char **argv) {
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

	run_simulation(args_info.messages_arg, args_info.corruption_arg, args_info.loss_arg, args_info.delay_arg, args_info.seed_arg);

    if (log_file != NULL) {
        fclose(log_file);
    }
    cmdline_parser_free(&args_info);
    return 0;
}
