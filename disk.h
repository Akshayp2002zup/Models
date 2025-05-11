#ifndef DISK_H
#define DISK_H

int disk_init(const char* filename, int size);
int disk_read_block(int block_num, void* buffer);
int disk_write_block(int block_num, const void* buffer);

#endif
