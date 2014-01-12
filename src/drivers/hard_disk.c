#include "../const/registers.h"
#include "../const/errors.h"
#include "../const/machine.h"
#include "../kernel/low_level.h"
#include "../debug/debug.h"
#include "hard_disk.h"

int read_sectors(int start_lba, char sectors_number, void* memory_buf) 
{
    if(start_lba + (int)sectors_number > MAX_LBA) 
    {
        print_msg("Given LBA plus sectors number exceed maximum LBA for disk\n");
        return LBA_EXCEED_DISK_SIZE;
    }
    
    unsigned char status;
    
    status = port_byte_in(REG_ATA_PRIMARY_7);                   // get status byte from ata device
    
    if(status & 0x88) 
    {
        port_byte_out(REG_ATA_PRIMARY_8, 0x04);
        port_byte_out(REG_ATA_PRIMARY_8, 0x00);                 // clear BSY and DRQ
        do
        {
            status = port_byte_in(REG_ATA_PRIMARY_7);
        }
        while((status & 0xc0) != 0x40);
    }
    
    int mask = 0x000000ff;
    
    port_byte_out(REG_ATA_PRIMARY_6, 0xe0);                     // 0x0e for master
    port_byte_out(REG_ATA_PRIMARY_2, sectors_number);           // sectors to read
    port_byte_out(REG_ATA_PRIMARY_3, start_lba & mask);         // low 8 bits of the LBA
    port_byte_out(REG_ATA_PRIMARY_4, (start_lba >> 8) & mask);  // medium 8 bits of the LBA
    port_byte_out(REG_ATA_PRIMARY_5, (start_lba >> 16) & mask); // high 8 bits of the LBA
    port_byte_out(REG_ATA_PRIMARY_7, 0x20);                     // READ command
        
    do 
    {
        status = port_byte_in(REG_ATA_PRIMARY_7);               // get status
        if(status & 0x21)                                       // DF or ERR is set?
        {
            print_msg("A disk read error occured before reading\n");
            return DISK_READ_ERROR;
        }
    }
    while(!(status & 0x08) && (status & 0x80));                 // while BSY is set and DRQ is clear
    
    unsigned int words = sectors_number * (BPS / 2);

    read_disk(words, REG_ATA_PRIMARY_0, memory_buf);
    
    status = port_byte_in(REG_ATA_PRIMARY_7);
    
    if(status & 0x21)                                           // DF or ERR is set?
    {
        print_msg("A disk read error occured after reading\n");
        return DISK_READ_ERROR;
    }

    return OK;
}    

int write_sectors(int start_lba, char sectors_number, void* memory_buf)
{
    if(start_lba + (int)sectors_number > MAX_LBA) 
    {
        print_msg("Given LBA plus sectors number exceed maximum LBA for disk\n");
        return LBA_EXCEED_DISK_SIZE;
    }
    
    unsigned char status;
    
    status = port_byte_in(REG_ATA_PRIMARY_7);                   // get status byte from ata device
    
    if(status & 0x88) 
    {
        port_byte_out(REG_ATA_PRIMARY_8, 0x04);
        port_byte_out(REG_ATA_PRIMARY_8, 0x00);                 // clear BSY and DRQ
        do
        {
            status = port_byte_in(REG_ATA_PRIMARY_7);
        }
        while((status & 0xc0) != 0x40);
    }
    
    int mask = 0x000000ff;
    
    port_byte_out(REG_ATA_PRIMARY_6, 0xe0);                     // 0x0e for master
    port_byte_out(REG_ATA_PRIMARY_2, sectors_number);           // sectors to read
    port_byte_out(REG_ATA_PRIMARY_3, start_lba & mask);         // low 8 bits of the LBA
    port_byte_out(REG_ATA_PRIMARY_4, (start_lba >> 8) & mask);  // medium 8 bits of the LBA
    port_byte_out(REG_ATA_PRIMARY_5, (start_lba >> 16) & mask); // high 8 bits of the LBA
    port_byte_out(REG_ATA_PRIMARY_7, 0x30);                     // WRITE command
        
    do 
    {
        status = port_byte_in(REG_ATA_PRIMARY_7);               // get status
        if(status & 0x21)                                       // DF or ERR is set?
        {
            print_msg("A disk read error occured before writing\n");
            return DISK_READ_ERROR;
        }
    }
    while(!(status & 0x08) && (status & 0x80));                 // while BSY is set and DRQ is clear
    
    unsigned int words = sectors_number * (BPS / 2);

    write_disk(words, REG_ATA_PRIMARY_0, memory_buf);
    
    status = port_byte_in(REG_ATA_PRIMARY_7);
    
    if(status & 0x21)                                           // DF or ERR is set?
    {
        print_msg("A disk read error occured after writing\n");
        return DISK_READ_ERROR;
    }
    
    port_byte_out(REG_ATA_PRIMARY_7, 0xe7);                     // FLUSH CACHE command

    return OK;
}
