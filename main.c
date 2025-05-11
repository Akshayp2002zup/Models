#include <stdio.h>
#include <string.h>
#include "fs_core.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: ./minifs <command> [args]\n");
        return 1;
    }

    if (strcmp(argv[1], "init") == 0) {
        fs_init("disk.bin", 1024 * 1024); // 1MB
    } else if (strcmp(argv[1], "open") == 0) {
        fs_open(argv[2]);
    } else if (strcmp(argv[1], "write") == 0) {
        fs_write(argv[2], argv[3]);
    } else if (strcmp(argv[1], "read") == 0) {
        char buffer[1024];
        fs_read(argv[2], buffer, sizeof(buffer));
        printf("%s\n", buffer);
    } else if (strcmp(argv[1], "flush") == 0) {
        cache_flush();
    } else {
        printf("Unknown command.\n");
    }
    return 0;
}
