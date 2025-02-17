#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "../inc/options.h"

static char *directory = ".";

void parse_arguments(int argc, char **argv) {
    int opt;
    while ((opt = getopt(argc, argv, "ldfs")) != -1) {
        switch (opt) {
            case 'l': opt_l = 1; break;
            case 'd': opt_d = 1; break;
            case 'f': opt_f = 1; break;
            case 's': opt_s = 1; break;
            default:
                fprintf(stderr, "Usage: %s [directory] [-ldfs]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (optind < argc) {
        directory = argv[optind];
    }
}

char *get_directory() {
    return directory;
}
