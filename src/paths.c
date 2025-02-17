#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "../inc/paths.h"

static char **paths = NULL;
static size_t paths_count = 0, paths_capacity = 0;

void add_path(const char *path) {
    if (paths_count >= paths_capacity) {
        paths_capacity = paths_capacity ? paths_capacity * 2 : 128;
        char **new_paths = realloc(paths, paths_capacity * sizeof(char *));
        if (!new_paths) {
            perror("realloc");
            free_paths();
            exit(EXIT_FAILURE);
        }
        paths = new_paths;
    }

    paths[paths_count] = strdup(path);
    if (!paths[paths_count]) {
        perror("strdup");
        free_paths();
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
    for (size_t i = 0; i  < paths_count; i++) {
        printf("%s\n", paths[i]);
    }
}

void free_paths() {
    for (size_t i = 0; i  < paths_count; i++) {
        free(paths[i]);
    }
    free(paths);
}