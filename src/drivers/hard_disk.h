#ifndef HARD_DISK_H
#define HARD_DISK_H

#include "../const/types.h"
/*read given number of sectors from disk, staring from start_lba and place them in memory*/
u8int read_sectors(u32int start_lba, u8int sectors_number, void* memory_buf);
/*write given number of sectors to disk, starting from start_lba, getting them from memory*/
u8int write_sectors(u32int start_lba, u8int sectors_number, void* memory_buf);

#endif
