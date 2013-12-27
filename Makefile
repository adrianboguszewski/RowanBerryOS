SRC = src
TARGET = target
CC = gcc
LINKER = ld
ASSEMBLER = nasm

C_SOURCES = $(wildcard $(SRC)/kernel/*.c)
HEADERS = $(wildcard $(SRC)/kernel/*.h)

# convert *.c to *.o and src to target
TMP = ${C_SOURCES:$(SRC)/%=$(TARGET)/%}
OBJ = ${TMP:.c=.o}

# default build target
all: image

image: $(TARGET)/boot.bin $(TARGET)/kernel.bin
	cat $^ > $(TARGET)/image

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
