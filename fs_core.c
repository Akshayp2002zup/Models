#include <stdio.h>
#include <string.h>
#include "fs_core.h"
#include "disk.h"
#include "cache.h"

#define MAX_FILES 10
#define MAX_BLOCKS_PER_FILE 8
#define BLOCK_SIZE 1024

typedef struct {
    char filename[32];
    int size;
    int block_pointers[MAX_BLOCKS_PER_FILE];
    int used;
} Inode;

static Inode inode_table[MAX_FILES];

int fs_init(const char* diskname, int size) {
    cache_init();
    return disk_init(diskname, size);
}

int find_inode(const char* filename) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (inode_table[i].used && strcmp(inode_table[i].filename, filename) == 0)
            return i;
    }
    return -1;
}

int fs_open(const char* filename) {
    int idx = find_inode(filename);
    if (idx != -1) return idx;
    for (int i = 0; i < MAX_FILES; i++) {
        if (!inode_table[i].used) {
            strncpy(inode_table[i].filename, filename, 31);
            inode_table[i].used = 1;
            inode_table[i].size = 0;
            memset(inode_table[i].block_pointers, -1, sizeof(inode_table[i].block_pointers));
            return i;
        }
    }
    return -1;
}

int fs_write(const char* filename, const char* data) {
    int idx = fs_open(filename);
    int data_len = strlen(data);
    int blocks_needed = (data_len + BLOCK_SIZE - 1) / BLOCK_SIZE;
    for (int i = 0; i < blocks_needed; i++) {
        inode_table[idx].block_pointers[i] = i;
        char block[BLOCK_SIZE] = {0};
        strncpy(block, data + (i * BLOCK_SIZE), BLOCK_SIZE);
        cache_write(i, block);
    }
    inode_table[idx].size = data_len;
    return 0;
}

int fs_read(const char* filename, char* buffer, int length) {
    int idx = find_inode(filename);
    if (idx == -1) return -1;
    int bytes_read = 0;
    for (int i = 0; i < MAX_BLOCKS_PER_FILE && inode_table[idx].block_pointers[i] != -1; i++) {
        char* data = cache_read(inode_table[idx].block_pointers[i]);
        strncpy(buffer + bytes_read, data, BLOCK_SIZE);
        bytes_read += BLOCK_SIZE;
    }
    buffer[inode_table[idx].size] = '\0';
    return inode_table[idx].size;
}

int fs_close(const char* filename) {
    return 0; // Not required for simulation
}
