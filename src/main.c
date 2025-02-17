#include <stdlib.h>
#include <locale.h>
#include "../inc/args.h"
#include "../inc/walk.h"
#include "../inc/paths.h"
#include "../inc/options.h"

int main(int argc, char **argv) {

    setlocale(LC_ALL, "");
    parse_arguments(argc, argv);
    walk(get_directory());
    if (opt_s) {
        sort_paths();
    }
    print_paths();
    free_paths();

    return EXIT_SUCCESS;
}