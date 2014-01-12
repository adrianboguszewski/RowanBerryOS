#ifndef HARD_DISK_H
#define HARD_DISK_H

/*read given number of sectors from disk, staring from start_lba and place them in memory*/
int read_sectors(int start_lba, char sectors_number, void* memory_buf);
/*write given number of sectors to disk, starting from start_lba getting them from memory*/
int write_sectors(int start_lba, char sectors_number, void* memory_buf);

#endif
