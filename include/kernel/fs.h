#ifndef FS_H
#define FS_H

#include "../include/types.h"

void fs_init();
char* fs_read_file(char* name);
void fs_list_files();

#endif
