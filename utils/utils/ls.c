
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdlib.h>

void list_directory(const char *path) {
    DIR *d = opendir(path);
    if (!d) {
        perror(path);
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(d)) != NULL) {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
            printf("%s\n", entry->d_name);
    }

    closedir(d);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        list_directory(".");
        return 0;
    }

    for (int i = 1; i < argc; ++i) {
        struct stat s;
        if (stat(argv[i], &s) == 0) {
            if (S_ISDIR(s.st_mode)) {
                printf("%s:\n", argv[i]);
                list_directory(argv[i]);
            } else {
                printf("%s\n", argv[i]);
            }
        } else {
            perror(argv[i]);
        }
    }

    return 0;
}

