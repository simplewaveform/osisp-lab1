#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <limits.h>

#ifndef PATH_MAX
#define PATH_MAX 4096  // Define a fallback if not present
#endif

#include "../inc/walk.h"
#include "../inc/paths.h"
#include "../inc/options.h"

void walk(const char *base_path) {
    DIR *dir = opendir(base_path);
    if (!dir) {
        fprintf(stderr, "dirwalk: cannot open '%s': %s\n", base_path, strerror(errno));
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

        int show = (!opt_l && !opt_d && !opt_f) || (opt_l && is_link) || (opt_d && is_dir) || (opt_f && is_reg);

        if (show) {
            add_path(full_path);
        }

        if (is_dir && !is_link) {
            walk(full_path);
        }
    }

    closedir(dir);
}
