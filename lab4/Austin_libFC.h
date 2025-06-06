#ifndef LIBFC_H
#define LIBFC_H

#define MAX_FILENAME_LEN 100
#define MAX_FILE_SIZE 1024

typedef int FCFile;

int fileCreate(const char *filename);

FCFile fileOpen(const char *filename);

int fileWrite(FCFile fd, const void *buffer, int size);

int fileRead(FCFile fd, void *buffer, int size);

int fileClose(FCFile fd);

int fileDelete(const char *filename);

#endif
