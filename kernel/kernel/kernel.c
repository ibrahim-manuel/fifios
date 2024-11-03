#include <stdio.h>
#include <kernel/video.h>
#include <stdint.h>
#include <stdbool.h>
#include <arch/i386/cpu.h>
#include "../../drivers/keyboard/keyboard.h"
#include "../../drivers/keyboard/statuscode.h"
#include "../../tty/tty.h"
#include "../mm/paging.h"
#include "../mm/kalloc.h"
#include "../../interrupts/idt.h"
#include "../../interrupts/pic.h"


extern int8_t final_kernel_phys_addr;

void kernel_main(void) 
{
    char pressed_char = '\0';
    init_mem_paging();
    init_page_allocator(&final_kernel_phys_addr, 4096*1024 - (int) &final_kernel_phys_addr);
    init_video();
    int8_t keyboard_init_status = init_keyboard();
    if(keyboard_init_status == OK || keyboard_init_status == DISABLE_CAPSLOCK_FAILED)
        printf("$");
    else
    {
        printf("Erro ao inicializar o teclado...");
        return; 
    }
    PIC_remap(0x20, 0x28);
    idt_init();

    while(true)
    {
        freeze();
    }
}


