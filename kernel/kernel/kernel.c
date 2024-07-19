#include <stdio.h>
#include <kernel/video.h>
#include <stdint.h>
#include <stdbool.h>
#include "../../drivers/keyboard/keyboard.h"
#include "../../drivers/keyboard/statuscode.h"
#include "../../tty/tty.h"
#include "../mm/paging.h"

void kernel_main(void) 
{
    char pressed_char = '\0';
    init_mem_paging();
    init_video();
    const int8_t keyboard_init_status = init_keyboard();
    if(keyboard_init_status == OK || keyboard_init_status == DISABLE_CAPSLOCK_FAILED)
        printf(">");
    else
    {
        printf("Erro ao inicializar o teclado...");
        return;
    }
    while(true)
    {
        term_main();
    }
}


