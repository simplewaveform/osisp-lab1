#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <locale.h>
#include <getopt.h>
#include <errno.h>

#define PATH_MAX 4096

int opt_l = 0;
int opt_d = 0;
int opt_f = 0;
int opt_s = 0;

char **paths = NULL;
size_t paths_count = 0;
size_t paths_capacity = 0;

void add_path(const char *path) {
    if (paths_count >= paths_capacity) {
        paths_capacity = (paths_capacity == 0) ? 128 : paths_capacity * 2;
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

void walk(const char *base_path) {
    DIR *dir = opendir(base_path);
    if (!dir) {
        fprintf(stderr, "dirwalk: cannot open directory '%s': %s\n", base_path, strerror(errno));
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        char full_path[PATH_MAX];
        snprintf(full_path, sizeof(full_path), "%s/%s", base_path, entry->d_name);

        struct stat st;
        if (lstat(full_path, &st) == -1) {
            fprintf(stderr, "dirwalk: cannot stat '%s': %s\n", full_path, strerror(errno));
            continue;
        }

        int is_link = S_ISLNK(st.st_mode);
        int is_dir = S_ISDIR(st.st_mode);
        int is_reg = S_ISREG(st.st_mode);

        int show;
        if (!opt_l && !opt_d && !opt_f) {
            show = (is_link || is_dir || is_reg);
        } else {
            show = (opt_l && is_link) || (opt_d && is_dir) || (opt_f && is_reg);
        }

        if (show) {
            if (opt_s) {
                add_path(full_path);
            } else {
                printf("%s\n", full_path);
            }
        }

        if (is_dir && !is_link) {
            walk(full_path);
        }
    }

    closedir(dir);
}

int compare(const void *a, const void *b) {
    return strcoll(*(const char **)a, *(const char **)b);
}

int main(int argc, char **argv) {
    setlocale(LC_COLLATE, "");

    int dir_found = 0;
    char *dir = ".";
    int new_argc = 0;
    char **new_argv = malloc(argc * sizeof(char *));

    new_argv[new_argc++] = argv[0];
    for (int i = 1; i < argc; ++i) {
        if (argv[i][0] == '-') {
            new_argv[new_argc++] = argv[i];
        } else {
            if (dir_found) {
                fprintf(stderr, "dirwalk: too many directories specified\n");
                free(new_argv);
                return EXIT_FAILURE;
            }
            dir = argv[i];
            dir_found = 1;
        }
    }

    int opt;
    while ((opt = getopt(new_argc, new_argv, "ldfs")) != -1) {
        switch (opt) {
            case 'l': opt_l = 1; break;
            case 'd': opt_d = 1; break;
            case 'f': opt_f = 1; break;
            case 's': opt_s = 1; break;
            default:
                fprintf(stderr, "Usage: %s [dir] [-ldfs]\n", argv[0]);
                free(new_argv);
                return EXIT_FAILURE;
        }
    }
    free(new_argv);

    walk(dir);

    if (opt_s) {
        qsort(paths, paths_count, sizeof(char *), compare);
        for (size_t i = 0; i < paths_count; ++i) {
            printf("%s\n", paths[i]);
            free(paths[i]);
        }
        free(paths);
    }

    return EXIT_SUCCESS;
}