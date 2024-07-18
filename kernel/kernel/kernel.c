#include <stdio.h>
#include <kernel/tty.h>
#include <stdint.h>
#include <stdbool.h>
#include "../arch/i386/drivers/keyboard/keyboard.h"
#include "../arch/i386/drivers/keyboard/statuscode.h"
#include "../mem/mem.h"

extern void enable_paging();
extern void load_page_directory(uint32_t* page_directory);

void kernel_main(void) {
    char pressed_char = '\0';
    init_page_directory();
    create_first_page_table();
    load_page_directory(page_directory);
    enable_paging();
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

