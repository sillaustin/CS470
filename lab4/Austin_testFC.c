#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Austin_libFC.h"

void prompt();

int main() {
    char filename[MAX_FILENAME_LEN];
    FCFile fd = -1;
    char buffer[1024];
    int choice;

    printf("Welcome to libFC Test App\n");

    while (1) {
        prompt();
        printf("Select option: ");
        if (scanf("%d", &choice) != 1) break;

        switch (choice) {
            case 1:
                // create file code
                snprintf(filename, sizeof(filename), "TEST.txt");
                if (fileCreate(filename) == 0) {
                    printf("File '%s' created.\n", filename);
                } else {
                    printf("Failed to create file.\n");
                }
                break;

            case 2:
                // open file code
                printf("Enter filename to open: ");
                scanf("%s", filename);
                fd = fileOpen(filename);
                if (fd >= 0) {
                    printf("File '%s' opened with fd %d.\n", filename, fd);
                } else {
                    printf("Failed to open file.\n");
                }
                break;

            case 3:
                // write to file code
                if (fd < 0) {
                    printf("Open a file first.\n");
                    break;
                }
                printf("Enter text to write (end with a blank line):\n");
                getchar(); //consume leftover newline
                buffer[0] = '\0';
                char line[256];
                while (fgets(line, sizeof(line), stdin)) {
                    if (strcmp(line, "\n") == 0) break;
                    strcat(buffer, line);
                }
                int written = fileWrite(fd, buffer, strlen(buffer));
                if (written >= 0) {
                    printf("Wrote %d bytes to file.\n", written);
                } else {
                    printf("Write failed.\n");
                }
                break;

            case 4:
                // display file contents code
                if (fd < 0) {
                    printf("Open a file first.\n");
                    break;
                }
                {
                    int readBytes = fileRead(fd, buffer, sizeof(buffer) - 1);
                    if (readBytes >= 0) {
                        buffer[readBytes] = '\0';
                        printf("File contents:\n%s\n", buffer);
                    } else {
                        printf("Read failed.\n");
                    }
                }
                break;

            case 5:
                // close file code
                if (fd < 0) {
                    printf("No file is open.\n");
                    break;
                }
                if (fileClose(fd) == 0) {
                    printf("File closed.\n");
                    fd = -1;
                } else {
                    printf("Close failed.\n");
                }
                break;

            case 6:
                // delete file code
                printf("Enter filename to delete: ");
                scanf("%s", filename);
                if (fileDelete(filename) == 0) {
                    printf("File '%s' deleted.\n", filename);
                } else {
                    printf("Delete failed.\n");
                }
                break;

            case 7:
                // exit program
                printf("Exiting...\n");
                if (fd >= 0) fileClose(fd);
                return 0;

            default:
                printf("Invalid choice.\n");
                break;
        }
    }
    return 0;
}

void prompt() {
    printf("\nMenu:\n");
    printf("1) Create introduction file\n");
    printf("2) Open file\n");
    printf("3) Write to file\n");
    printf("4) Read from file\n");
    printf("5) Close file\n");
    printf("6) Delete file\n");
    printf("7) Exit\n");
}
