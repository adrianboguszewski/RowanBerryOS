SRC = src
TARGET = target
CC = gcc
LINKER = ld
ASSEMBLER = nasm
SHELL=/bin/bash
SIZE=`ls -l $(TARGET)/image | cut -d' ' -f5`
# while kernel less than 64kB
SIZE1=$$((65536 - $(SIZE)))
# disk size = 126 MB
SIZE2=$$(((132120576 - $(SIZE)) / 512))

BOOT_SOURCES = $(wildcard $(SRC)/boot/*.asm)
ASM_SOURCES = $(wildcard $(SRC)/kernel/*.asm $(SRC)/debug/*.asm $(SRC)/kernel/idt/*.asm)
C_SOURCES = $(wildcard $(SRC)/kernel/*.c $(SRC)/drivers/*.c $(SRC)/debug/*.c $(SRC)/kernel/idt/*.c $(SRC)/kernel/heap/*.c)
HEADERS = $(wildcard $(SRC)/kernel/*.h $(SRC)/drivers/*.h $(SRC)/debug/*.h $(SRC)/kernel/idt/*.h $(SRC)/const/*.h $(SRC)/kernel/heap/*.h)

# convert *.c to *.o and src to target
TMP = ${C_SOURCES:$(SRC)/%=$(TARGET)/%}
OBJ = ${TMP:.c=.o}
# convert *.asm to *.o and src to target
TMP2 = ${ASM_SOURCES:$(SRC)/%=$(TARGET)/%}
OBJ2 = ${TMP2:.asm=.o}

# default build target
all: clean image
	
image: $(TARGET)/boot.bin $(TARGET)/kernel.bin
	cat $^ > $(TARGET)/image
	dd if=/dev/zero of=$(TARGET)/tmp bs=1 count=$(SIZE1)
	cat $(TARGET)/tmp >> $(TARGET)/image
	dd if=/dev/zero of=$(TARGET)/tmp2 bs=512 count=$(SIZE2)
	cat $(TARGET)/tmp2 >> $(TARGET)/image

$(TARGET)/kernel.bin: ${OBJ} ${OBJ2}
	$(LINKER) -o $@ -Ttext 0x1000 $^ --oformat binary -m elf_i386

$(TARGET)/%.o: $(SRC)/%.c ${HEADERS}
	$(CC) -ffreestanding -Wall -std=gnu99 -c $< -o $@ -m32
	
$(TARGET)/%.o: $(SRC)/%.asm
	$(ASSEMBLER) $< -f elf -o $@

$(TARGET)/%.bin: $(SRC)/boot/%.asm
	$(ASSEMBLER) $< -f bin -i $(SRC)/ -o $@
	
clean:
	rm -rf $(TARGET)/
	mkdir -p $(TARGET)/kernel/heap
	mkdir -p $(TARGET)/kernel/idt
	mkdir $(TARGET)/drivers
	mkdir $(TARGET)/debug
