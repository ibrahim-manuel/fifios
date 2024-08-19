#ifndef KALLOC_H
#define KALLOC_H
#include <stdint.h>

#define PAGE_SIZE 0x1000

typedef struct free_page_t 
{
    struct free_page_t* next;  // Próxima página livre na lista
} free_page_t;

typedef struct 
{
    free_page_t* free_list;  // Cabeça da lista de páginas livres
    uint32_t total_pages;
} page_allocator_t;


void init_page_allocator( void* memory_start, size_t memory_size);
void* kalloc();
void kfree(void* page);

#endif