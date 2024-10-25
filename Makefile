# Definições de compilador e flags
CC = i386-elf-gcc
ASM = nasm
CFLAGS = -Wall -Wextra -ffreestanding -nostdlib -Ilibc/include -Ikernel/include
LDFLAGS = -T linker.ld -ffreestanding -nostdlib

# Estrutura de diretórios
SRC_DIR = kernel arch/i386 kernel/include/kernel kernel/kernel libc/include/sys libc/include libc/stdio libc/stdlib libc/string
OUTPUT_DIR = _output

# Listagem dos arquivos fonte
ASM_SOURCES = $(wildcard kernel/arch/i386/*.asm)
C_SOURCES = $(wildcard kernel/arch/i386/*.c drivers/keyboard/*.c drivers/disk/*.c kernel/mm/*.c  kernel/kernel/*.c tty/*.c libc/stdio/*.c libc/stdlib/*.c libc/string/*.c)

# Geração das listas de objetos
ASM_OBJECTS = $(patsubst kernel/arch/i386/%.asm, _output/kernel/arch/i386/%.o, $(ASM_SOURCES))
C_OBJECTS = $(patsubst %.c, _output/%.o, $(C_SOURCES))

# Alvo padrão
all: $(OUTPUT_DIR)/kernel.elf
	@echo "Compilação e linkagem completas!"

# Regras de linkagem para gerar o kernel.elf
$(OUTPUT_DIR)/kernel.elf: $(ASM_OBJECTS) $(C_OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^

# Regras de compilação para arquivos asm
_output/kernel/arch/i386/%.o: kernel/arch/i386/%.asm
	@mkdir -p $(dir $@)
	$(ASM) -f elf32 -o $@ $<

# Regras de compilação para arquivos c
_output/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

# Limpeza dos arquivos compilados
clean:
	rm -rf $(OUTPUT_DIR)

.PHONY: all clean
