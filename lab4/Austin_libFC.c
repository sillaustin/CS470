#include "Austin_libFC.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char name[MAX_FILENAME_LEN];
    char data[MAX_FILE_SIZE];
    int size;
    int is_open;
} FileEntry;

#define MAX_FILES 10

static FileEntry files[MAX_FILES];
static FCFile openFiles[MAX_FILES]; //maps fd to file index, -1 if closed

//initialize files and openFiles arrays (one time)
static void initFS() {
    static int initialized = 0;
    if (initialized) return;
    for (int i = 0; i < MAX_FILES; i++) {
        files[i].name[0] = '\0';
        files[i].size = 0;
        files[i].is_open = 0;
        openFiles[i] = -1;
    }
    initialized = 1;
}

int fileCreate(const char *filename) {
    initFS();
    for (int i = 0; i < MAX_FILES; i++) {
        if (files[i].name[0] == '\0') {
            strncpy(files[i].name, filename, MAX_FILENAME_LEN - 1);
            files[i].name[MAX_FILENAME_LEN -1] = '\0';
            files[i].size = 0;
            files[i].is_open = 0;
            return 0; //success
        }
        if (strcmp(files[i].name, filename) == 0) {
            return -1; //file already exists
        }
    }
    return -1; //no space left
}

FCFile fileOpen(const char *filename) {
    initFS();
    for (int i = 0; i < MAX_FILES; i++) {
        if (strcmp(files[i].name, filename) == 0) {
            if (files[i].is_open) return -1; //already open
            files[i].is_open = 1;
            for (int fd = 0; fd < MAX_FILES; fd++) {
                if (openFiles[fd] == -1) {
                    openFiles[fd] = i;
                    return fd;
                }
            }
            return -1; //no available fd
        }
    }
    return -1; //file not found
}

int fileWrite(FCFile fd, const void *buffer, int size) {
    if (fd < 0 || fd >= MAX_FILES || openFiles[fd] == -1) return -1;
    int idx = openFiles[fd];
    if (size > MAX_FILE_SIZE) size = MAX_FILE_SIZE;
    memcpy(files[idx].data, buffer, size);
    files[idx].size = size;
    return size;
}

int fileRead(FCFile fd, void *buffer, int size) {
    if (fd < 0 || fd >= MAX_FILES || openFiles[fd] == -1) return -1;
    int idx = openFiles[fd];
    if (size > files[idx].size) size = files[idx].size;
    memcpy(buffer, files[idx].data, size);
    return size;
}

int fileClose(FCFile fd) {
    if (fd < 0 || fd >= MAX_FILES || openFiles[fd] == -1) return -1;
    int idx = openFiles[fd];
    files[idx].is_open = 0;
    openFiles[fd] = -1;
    return 0;
}

int fileDelete(const char *filename) {
    initFS();
    for (int i = 0; i < MAX_FILES; i++) {
        if (strcmp(files[i].name, filename) == 0) {
            if (files[i].is_open) return -1; //cannot delete open file
            files[i].name[0] = '\0';
            files[i].size = 0;
            return 0; //success
        }
    }
    return -1; //file not found
}
