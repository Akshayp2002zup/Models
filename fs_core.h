#ifndef FS_CORE_H
#define FS_CORE_H

int fs_init(const char* diskname, int size);
int fs_open(const char* filename);
int fs_write(const char* filename, const char* data);
int fs_read(const char* filename, char* buffer, int length);
int fs_close(const char* filename);

void cache_flush();

#endif
