#include "argparse/argparse.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    struct gengetopt_args_info args_info;

    if (cmdline_parser(argc, argv, &args_info) != 0) {
        exit(1);
    }

    cmdline_parser_free(&args_info);
    return 0;
}
