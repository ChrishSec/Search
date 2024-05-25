// DEVELOPED BY >> ChrishSec

// Website: https://ChrishSec.com
// GitHub: https://github.com/ChrishSec
// Twitter: https://twitter.com/ChrishSec

// This project was inspired by and includes code from [Alex Petrusca's assembly-virus repository](https://raw.githubusercontent.com/AlexPetrusca/assembly-virus/master/crawl.c).
// Thanks to Alex Petrusca for providing the code and ideas that helped shape this project.

/*

C:\Users\User\Documents\Projects\Search>search.exe

 DEVELOPED BY >> ChrishSec

 Usage: search.exe <file> OR <folder> [path] -v


C:\Users\User\Documents\Projects\Search>search.exe flag.txt C:\Users\User\Desktop

Found 5 occurrence(s) of 'flag.txt':
  1) FILE = C:\Users\User\Desktop\1\flag.txt | Attributes: ARCHIVE
  2) FILE = C:\Users\User\Desktop\2\flag.txt | Attributes: ARCHIVE
  3) FILE = C:\Users\User\Desktop\3\flag.txt | Attributes: ARCHIVE
  4) FILE = C:\Users\User\Desktop\4\flag.txt | Attributes: ARCHIVE
  5) FILE = C:\Users\User\Desktop\flag.txt | Attributes: ARCHIVE

C:\Users\User\Documents\Projects\Search>search.exe ChrishSec C:\Users\User\Desktop

Found 4 occurrence(s) of 'ChrishSec':
  1) DIR = C:\Users\User\Desktop\1\ChrishSec | Attributes: DIRECTORY
  2) DIR = C:\Users\User\Desktop\2\ChrishSec | Attributes: DIRECTORY
  3) DIR = C:\Users\User\Desktop\3\ChrishSec | Attributes: DIRECTORY
  4) DIR = C:\Users\User\Desktop\4\ChrishSec | Attributes: DIRECTORY

C:\Users\User\Documents\Projects\Search>

*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define DEFAULT_PATH "C:\\"
//#define DEFAULT_PATH "E:\\"
#define PATH_LENGTH 260
#define STACK_SIZE 2000

typedef struct {
    char path[PATH_LENGTH];
    DWORD attributes;
} SearchResult;

char* getAttrString(char *attributes, DWORD fileAttributes) {
    attributes[0] = '\0';
    if (fileAttributes & FILE_ATTRIBUTE_READONLY) strcat(attributes, "READONLY ");
    if (fileAttributes & FILE_ATTRIBUTE_HIDDEN) strcat(attributes, "HIDDEN ");
    if (fileAttributes & FILE_ATTRIBUTE_SYSTEM) strcat(attributes, "SYSTEM ");
    if (fileAttributes & FILE_ATTRIBUTE_DIRECTORY) strcat(attributes, "DIRECTORY ");
    if (fileAttributes & FILE_ATTRIBUTE_ARCHIVE) strcat(attributes, "ARCHIVE ");
    if (fileAttributes & FILE_ATTRIBUTE_NORMAL) strcat(attributes, "NORMAL ");
    if (fileAttributes & FILE_ATTRIBUTE_TEMPORARY) strcat(attributes, "TEMPORARY ");
    if (fileAttributes & FILE_ATTRIBUTE_COMPRESSED) strcat(attributes, "COMPRESSED ");
    if (fileAttributes & FILE_ATTRIBUTE_OFFLINE) strcat(attributes, "OFFLINE ");
    if (fileAttributes & FILE_ATTRIBUTE_NOT_CONTENT_INDEXED) strcat(attributes, "NOT_CONTENT_INDEXED ");
    if (fileAttributes & FILE_ATTRIBUTE_ENCRYPTED) strcat(attributes, "ENCRYPTED ");
    return attributes;
}

void search(char *basePath, char *filename, int verbose, SearchResult *results, int *count) {
    char path[PATH_LENGTH];
    char attributes[1024];
    WIN32_FIND_DATA findData;
    HANDLE handle;

    snprintf(path, sizeof(path), "%s\\*.*", basePath);
    handle = FindFirstFile(path, &findData);

    if (handle == INVALID_HANDLE_VALUE) {
        return;
    }

    do {
        if (strcmp(findData.cFileName, ".") != 0 && strcmp(findData.cFileName, "..") != 0) {
            snprintf(path, sizeof(path), "%s\\%s", basePath, findData.cFileName);

            if (verbose) {
                printf("Found: %s = %s | Attributes: %s\n", 
                       (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ? "DIR" : "FILE",
                       path, getAttrString(attributes, findData.dwFileAttributes));
            }

            if (strcmp(findData.cFileName, filename) == 0) {
                strncpy(results[*count].path, path, PATH_LENGTH);
                results[*count].attributes = findData.dwFileAttributes;
                (*count)++;
            }

            if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                search(path, filename, verbose, results, count);
            }
        }
    } while (FindNextFile(handle, &findData) != 0);

    FindClose(handle);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("\n DEVELOPED BY >> ChrishSec\n");
        printf("\n Usage: %s <file> OR <folder> [path] -v\n\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    char *path = DEFAULT_PATH;
    int verbose = 0;
    SearchResult results[PATH_LENGTH];
    int count = 0;

    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "-v") == 0) {
            verbose = 1;
        } else {
            path = argv[i];
        }
    }

    search(path, filename, verbose, results, &count);

    if (count > 0) {
        printf("\nFound %d occurrence(s) of '%s':\n", count, filename);
        for (int i = 0; i < count; i++) {
            char attributes[1024];
            printf("  %d) %s = %s | Attributes: %s\n", i + 1,
                   (results[i].attributes & FILE_ATTRIBUTE_DIRECTORY) ? "DIR" : "FILE",
                   results[i].path, getAttrString(attributes, results[i].attributes));
        }
    } else {
        printf("\nFile or folder '%s' not found.\n", filename);
    }

    return 0;
}