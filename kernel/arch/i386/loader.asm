bits 32
section .text
	; Especificações multiboot
	align 4
	dd 0x1BADB002			; magic
	dd 0x00				; flags
	dd - (0x1BADB002 + 0x00)	; checksum. m+f+c tem de ser zero

	global start
	extern kernel_main

	; GDT setup
	gdt_start:
		gdt_null:     ; null descriptor
		dd 0x0
		dd 0x0

	gdt_code:       ; code segment descriptor
		dd 0x0000FFFF
		dd 0x00CF9A00

	gdt_data:       ; data segment descriptor
		dd 0x0000FFFF
		dd 0x00CF9200

	gdt_end:

	gdt_descriptor:
		dw gdt_end - gdt_start - 1
		dd gdt_start

	; Function to load GDT
	load_gdt:
		lgdt [gdt_descriptor]
		ret
		
	start:
		cli  ; Desativa interrupções
		call load_gdt
		; Ativa o modo protegido
		mov eax, cr0
		or eax, 0x1
		mov cr0, eax
		; Salta para o modo protegido
		jmp 0x08:start_protected

	start_protected:
		; Configura os segmentos de dados
		mov ax, 0x10
		mov ds, ax
		mov es, ax
		mov fs, ax
		mov gs, ax
		mov ss, ax
		; Configura a pilha
		mov esp, 0x90000

		call kernel_main
		hlt ; Coloca a CPU em "pause"