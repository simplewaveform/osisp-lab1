#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/paths.h"

static char **paths = NULL;
static size_t paths_count = 0, paths_capacity = 0;

void add_path(const char *path) {
    if (paths_count >= paths_capacity) {
        paths_capacity = paths_capacity ? paths_capacity * 2 : 128;
        paths = realloc(paths, paths_capacity * sizeof(char *));
        if (!paths) {
            perror("realloc");
            exit(EXIT_FAILURE);
        }
    }
    paths[paths_count] = strdup(path);
    if (!paths[paths_count]) {
        perror("strdup");
        exit(EXIT_FAILURE);
    }
    paths_count++;
}

int compare(const void *a, const void *b) {
    return strcoll(*(const char **)a, *(const char **)b);
}

void sort_paths() {
    qsort(paths, paths_count, sizeof(char *), compare);
}

void print_paths() {
    for (size_t i = 0; i < paths_count; i++) {
        printf("%s\n", paths[i]);
    }
}

void free_paths() {
    for (size_t i = 0; i < paths_count; i++) {
        free(paths[i]);
    }
    free(paths);
}
