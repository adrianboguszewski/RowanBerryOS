// machine constants
#define HPC 16                                         // heads per cylinder
#define SPT 63                                         // sectors per head
#define CPH 256                                        // cylinders per head
#define BPS 512                                        // bytes per sector
#define LBA(c, h, s) ((c * HPC) + h) * SPT + s - 1     // LBA from CHS
#define MAX_LBA LBA(CPH, HPC, SPT)                     // max LBA
#define MEMORY_MB 32                                   // memory in MB
#define MAX_MEMORY_ADDRESS (1 << 20) * MEMORY_MB - 1   // max memory address
