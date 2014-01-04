#ifndef _HARD_DISK_H
#define _HARD_DISK_H

int read_sectors(int start_lba, char sectors_number, void* memory_buf);
int write_sectors(int start_lba, char sectors_number, void* memory_buf);

#endif
