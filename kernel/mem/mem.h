#ifndef MEM_MANAGER_H
#define MEM_MANAGER_H

#include <stdint.h>

uint32_t page_directory[1024] __attribute__((aligned(4096))); // as entradas são armazenadas em endereços que são multiplos de 4kb partindo do primeiro endereço.
uint32_t first_page_table[1024] __attribute__((aligned(4096)));
void init_page_directory();
void create_first_page_table();

void init_page_directory(){
    for(int i = 0; i < 1024; i++){
        page_directory[i] = 0x00000002;
    }
}

void create_first_page_table(){
    for(int i = 0; i < 1024; i++){
        first_page_table[i] = (i * 0x1000) | 3; // atributos: supervisor level, read/write, present.
    }
    page_directory[0] = ((unsigned int)first_page_table) | 3;
}

#endif

