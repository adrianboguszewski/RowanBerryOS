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

ASM_SOURCES = $(wildcard $(SRC)/kernel/*.asm $(SRC)/boot/*.asm)
C_SOURCES = $(wildcard $(SRC)/kernel/*.c $(SRC)/drivers/*.c)
HEADERS = $(wildcard $(SRC)/kernel/*.h $(SRC)/drivers/*.h $(SRC)/const/*.h)

# convert *.c to *.o and src to target
TMP = ${C_SOURCES:$(SRC)/%=$(TARGET)/%}
OBJ = ${TMP:.c=.o}

# default build target
all: clean image
	
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
	
replace:
	sed -i 's/\t/    /g' ${HEADERS} ${C_SOURCES} ${ASM_SOURCES}
	
clean:
	rm -rf $(TARGET)/
	mkdir $(TARGET)
	mkdir $(TARGET)/kernel
	mkdir $(TARGET)/drivers
