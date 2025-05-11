#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "disk.h"
#include "cache.h"

#define CACHE_SIZE 8
#define BLOCK_SIZE 1024

typedef struct {
    int block_num;
    char data[BLOCK_SIZE];
    bool dirty;
    bool valid;
} CacheBlock;

static CacheBlock cache[CACHE_SIZE];

void cache_init() {
    for (int i = 0; i < CACHE_SIZE; i++) {
        cache[i].valid = false;
        cache[i].dirty = false;
    }
}

int find_cache_index(int block_num) {
    for (int i = 0; i < CACHE_SIZE; i++) {
        if (cache[i].valid && cache[i].block_num == block_num)
            return i;
    }
    return -1;
}

char* cache_read(int block_num) {
    int index = find_cache_index(block_num);
    if (index == -1) {
        index = block_num % CACHE_SIZE;
        disk_read_block(block_num, cache[index].data);
        cache[index].block_num = block_num;
        cache[index].valid = true;
        cache[index].dirty = false;
    }
    return cache[index].data;
}

void cache_write(int block_num, const char* data) {
    int index = find_cache_index(block_num);
    if (index == -1) {
        index = block_num % CACHE_SIZE;
        disk_read_block(block_num, cache[index].data);
        cache[index].block_num = block_num;
        cache[index].valid = true;
    }
    memcpy(cache[index].data, data, BLOCK_SIZE);
    cache[index].dirty = true;
}

void cache_flush() {
    for (int i = 0; i < CACHE_SIZE; i++) {
        if (cache[i].valid && cache[i].dirty) {
            disk_write_block(cache[i].block_num, cache[i].data);
            cache[i].dirty = false;
        }
    }
}
