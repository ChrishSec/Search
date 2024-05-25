// DEVELOPED BY >> ChrishSec

// Website: https://ChrishSec.com
// GitHub: https://github.com/ChrishSec
// Twitter: https://twitter.com/ChrishSec

/*

$ ./search
Usage: ./search <file> OR <folder>

$ ./search findme.xt
Found FILE: /home/user/Downloads/FindMe/findme.xt
Found FILE: /home/user/Music/FindMe/findme.xt
Found FILE: /home/user/Documents/FindMe/findme.xt

$ cat /home/user/Documents/FindMe/findme.xt
YOu gOt it!

$ ./search FindMe
Found DIR: /home/user/Downloads/FindMe
Found DIR: /home/user/Music/FindMe
Found DIR: /home/user/Documents/FindMe

$ cat /home/user/Documents/FindMe/findme.xt
YOu gOt it!

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>

#define PATH_LEN 1024

void search(const char *basePath, const char *target) {
    DIR *directory;
    struct dirent *entry;
    struct stat status;

    if (!(directory = opendir(basePath))) {
        return;
    }

    int isRoot = (strcmp(basePath, "/") == 0);

    while ((entry = readdir(directory)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char path[PATH_LEN];
        if (isRoot) {
            snprintf(path, sizeof(path), "%s%s", basePath, entry->d_name);
        } else {
            snprintf(path, sizeof(path), "%s/%s", basePath, entry->d_name);
        }

        if (lstat(path, &status) == -1) {
            continue;
        }

        if (S_ISDIR(status.st_mode)) {
            search(path, target);

            if (strcmp(entry->d_name, target) == 0) {
                printf(" Found DIR: %s\n", path);
            }
        } else {
            if (strcmp(entry->d_name, target) == 0) {
                printf(" Found FILE: %s\n", path);
            }
        }
    }

    closedir(directory);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("\n DEVELOPED BY >> ChrishSec\n");
        printf("\n Usage: %s <file> OR <folder>\n\n", argv[0]);
        return 1;
    }

    char *basepath = "/";
    char *target = argv[1];

    search(basepath, target);

    return 0;
}