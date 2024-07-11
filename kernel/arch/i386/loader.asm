bits 32
section .text
	;Especificações multiboot
	align 4
	dd 0x1BADB002			;magic
	dd 0x00				;flags
	dd - (0x1BADB002 + 0x00)	;checksum. m+f+c tem de ser zero

global start
extern kernel_main

start:
	cli  ; para as interrupções

	call kernel_main

	hlt ; coloca a cpu em "pause"