#include <stddef.h>
#include "paging.h"

uint32_t kernel_pg_dir[1024] __attribute__((aligned(4096))); 
uint32_t kernel_first_pg_table[1024] __attribute__((aligned(4096)));
extern void enable_paging();
extern void load_page_directory(uint32_t* kernel_pg_dir);

void init_page_directory(uint32_t* pgdir)
{
    for(int i = 0; i < 1024; i++)
        pgdir[i] = 0x00000002;
}

void create_page_table(uint32_t* pgdir, uint32_t* pg_table, int16_t pg_table_idx)
{
    for(int i = 0; i < 1024; i++)
        pg_table[i] = (i * PAGE_SIZE) | 3; // atributos: supervisor level, read/write, present.
    pgdir[pg_table_idx] = ((unsigned int)pg_table) | 3;
}

void init_mem_paging()
{
    init_page_directory(kernel_pg_dir);
    create_page_table(kernel_pg_dir, kernel_first_pg_table, 0);
    load_page_directory(kernel_pg_dir);
    enable_paging();
}

