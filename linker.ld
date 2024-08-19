/*
 * linker.ld
 */

OUTPUT_FORMAT(elf32-i386)
ENTRY(start)
SECTIONS
{
	/* Posiciona o kernel a 1Mb do endereço mais baixo da memória */
	. = 0x100000;
	
	/* Código excutável */
	.text : {*(.text)}
	
	/* Dados inicializados */
	.data : {*(.data)}

	/* Dados não inicializados e stack */
	.bss  : {*(.bss)}

	. = ALIGN(4096);

    /* Definir o símbolo após o alinhamento */
    PROVIDE(final_kernel_phys_addr = .);

	/* O compilador provavelmente vai adicionar outras secções */
}