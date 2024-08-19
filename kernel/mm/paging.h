#ifndef MEM_PAGING_H
#define MEM_PAGING_H
#include <stdint.h>

extern uint32_t kernel_pg_dir[1024] __attribute__((aligned(4096))); 
extern uint32_t kernel_first_pg_table[1024] __attribute__((aligned(4096)));;

void init_page_directory(uint32_t* pgdir);
void create_first_page_table(uint32_t* pgdir, uint32_t* pg_table, int16_t pg_table_idx);
void init_mem_paging();

#endif