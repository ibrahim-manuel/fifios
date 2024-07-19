#ifndef MEM_PAGING_H
#define MEM_PAGING_H

#include <stdint.h>

extern uint32_t page_directory[1024] __attribute__((aligned(4096))); 
extern uint32_t first_page_table[1024] __attribute__((aligned(4096)));

void init_page_directory();
void create_first_page_table();
void init_mem_paging();

#endif