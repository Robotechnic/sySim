#include "argparse/argparse.h"
#include "logger/log.h"
#include "simulator/simulator.h"
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_CONFIG_FILE "config.ini"

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

    if (args_info->loss_arg < 0 || args_info->loss_arg > 1) {
        fprintf(stderr, "Loss probability must be between 0 and 1\n");
        return false;
    }

    if (args_info->corruption_arg < 0 || args_info->corruption_arg > 1) {
        fprintf(stderr, "Corruption probability must be between 0 and 1\n");
        return false;
    }

    if (args_info->delay_arg < 0) {
        fprintf(stderr, "Delay must be at least 0\n");
        return false;
    }

    return true;
}

void parse_config_file(const char *name, struct gengetopt_args_info *args_info) {
    struct cmdline_parser_params *params;
    params = cmdline_parser_params_create();
    params->initialize = 0;
    params->override = 0;

    if (cmdline_parser_config_file(name, args_info, params) != 0) {
        free(params);
        exit(1);
    }
    free(params);
}

/**
 * @brief Check if there is a default config file in the current directory
 *
 * @return true if the file is here
 */
bool is_config_file_here() {
    FILE *file = fopen(DEFAULT_CONFIG_FILE, "r");
    if (file == NULL) {
        return false;
    }
    fclose(file);
    return true;
}

int main(int argc, char **argv) {
    struct gengetopt_args_info args_info;

    if (cmdline_parser(argc, argv, &args_info) != 0) {
        return 1;
    }

    if (args_info.conf_file_given) {
        parse_config_file(args_info.conf_file_arg, &args_info);
    } else if (is_config_file_here()) {
        parse_config_file(DEFAULT_CONFIG_FILE, &args_info);
    }

	if (args_info.visualize_arg) {
		log_warn("Visualization is not implemented yet");
	}

    FILE *log_file = NULL;
    if (!check_args(&args_info, log_file)) {
        cmdline_parser_free(&args_info);
        return 1;
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
                               .check = args_info.check_flag,
                               .ignore_failure = args_info.ignore_failure_flag};

    bool simulation_ok = run_simulation(&config);

    if (log_file != NULL) {
        fclose(log_file);
    }
    cmdline_parser_free(&args_info);
    if (!simulation_ok) {
        return 2;
    }
    return 0;
}
