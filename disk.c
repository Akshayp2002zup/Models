#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "disk.h"

#define BLOCK_SIZE 1024
static FILE* disk_file = NULL;

int disk_init(const char* filename, int size) {
    disk_file = fopen(filename, "wb+");
    if (!disk_file) return -1;
    char zero[BLOCK_SIZE] = {0};
    for (int i = 0; i < size / BLOCK_SIZE; i++) {
        fwrite(zero, 1, BLOCK_SIZE, disk_file);
    }
    fclose(disk_file);
    return 0;
}

int disk_read_block(int block_num, void* buffer) {
    disk_file = fopen("disk.bin", "rb");
    fseek(disk_file, block_num * BLOCK_SIZE, SEEK_SET);
    fread(buffer, 1, BLOCK_SIZE, disk_file);
    fclose(disk_file);
    return 0;
}

int disk_write_block(int block_num, const void* buffer) {
    disk_file = fopen("disk.bin", "rb+");
    fseek(disk_file, block_num * BLOCK_SIZE, SEEK_SET);
    fwrite(buffer, 1, BLOCK_SIZE, disk_file);
    fclose(disk_file);
    return 0;
}
