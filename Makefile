SRC = src
TARGET = target
CC = gcc
LINKER = ld
ASSEMBLER = nasm
SHELL=/bin/bash
SIZE=`ls -l $(TARGET)/image | cut -d' ' -f5`
# while kernel less than 64kB
SIZE1=$$((65536 - $(SIZE)))
# disk size = 128 MB
SIZE2=$$(((134217728 - $(SIZE)) / 512))

C_SOURCES = $(wildcard $(SRC)/kernel/*.c)
HEADERS = $(wildcard $(SRC)/kernel/*.h)

# convert *.c to *.o and src to target
TMP = ${C_SOURCES:$(SRC)/%=$(TARGET)/%}
OBJ = ${TMP:.c=.o}

# default build target
all: image
	
image: $(TARGET)/boot.bin $(TARGET)/kernel.bin
	cat $^ > $(TARGET)/image
	dd if=/dev/zero of=$(TARGET)/tmp bs=1 count=$(SIZE1)
	cat $(TARGET)/tmp >> $(TARGET)/image
	dd if=/dev/zero of=$(TARGET)/tmp2 bs=512 count=$(SIZE2)
	cat $(TARGET)/tmp2 >> $(TARGET)/image

$(TARGET)/kernel.bin: $(TARGET)/kernel_entry.o ${OBJ}
	$(LINKER) -o $@ -Ttext 0x1000 $^ --oformat binary -m elf_i386

$(TARGET)/%.o: $(SRC)/%.c ${HEADERS}
	$(CC) -ffreestanding -Wall -c $< -o $@ -m32
	
$(TARGET)/%.o: $(SRC)/kernel/%.asm
	$(ASSEMBLER) $< -f elf -o $@

$(TARGET)/%.bin: $(SRC)/boot/%.asm
	$(ASSEMBLER) $< -f bin -i $(SRC)/ -o $@
	
clean:
	rm -rf $(TARGET)/*
	mkdir $(TARGET)/kernel
