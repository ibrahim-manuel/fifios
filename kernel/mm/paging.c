#include "paging.h"

uint32_t page_directory[1024] __attribute__((aligned(4096))); 
uint32_t first_page_table[1024] __attribute__((aligned(4096)));

extern void enable_paging();
extern void load_page_directory(uint32_t* page_directory);

void init_page_directory()
{
    for(int i = 0; i < 1024; i++){
        page_directory[i] = 0x00000002;
    }
}

void create_first_page_table()
{
    for(int i = 0; i < 1024; i++){
        first_page_table[i] = (i * 0x1000) | 3; // atributos: supervisor level, read/write, present.
    }
    page_directory[0] = ((unsigned int)first_page_table) | 3;
}

void init_mem_paging()
{
    init_page_directory();
    create_first_page_table();
    load_page_directory(page_directory);
    enable_paging();
}
