#ifndef CACHE_H
#define CACHE_H

void cache_init();
char* cache_read(int block_num);
void cache_write(int block_num, const char* data);
void cache_flush();

#endif
