#include <stdio.h>
#include <kernel/tty.h>
#include <stdint.h>
#include <stdbool.h>
#include "../arch/i386/drivers/keyboard/keyboard.h"
#include "../arch/i386/drivers/keyboard/statuscode.h"

void kernel_main(void) {
    char pressed_char = '\0';
    terminal_initialize();
    const int keyboard_init_status = keyboard_initialize();
    if(keyboard_init_status == OK || keyboard_init_status == DISABLE_CAPSLOCK_FAILED)
        printf(">");
    else{
        printf("Erro ao inicializar o teclado...");
        return;
    }
    while(true){
        terminal_main();
    }
}

