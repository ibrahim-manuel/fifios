bits 32
section .text
    ; Código para habilitar a paginação
    global load_page_directory
    global enable_paging
	load_page_directory:
		push ebp
		mov ebp, esp
		mov eax, [esp + 8]
		mov cr3, eax
		mov esp, ebp
		pop ebp
		ret
	enable_paging:
		push ebp
		mov ebp, esp
		mov eax, cr0
		or eax, 0x80000000
		mov cr0, eax
		mov esp, ebp
		pop ebp
		ret
