#include <stddef.h>
#include "kalloc.h"

static page_allocator_t allocator;

void init_page_allocator(void* memory_start, size_t memory_size) 
{
    allocator.free_list = (free_page_t*)memory_start;
    allocator.total_pages = memory_size / PAGE_SIZE;

    free_page_t* current = allocator.free_list;
    for (size_t i = 0; i < allocator.total_pages - 1; i++) {
        current->next = (free_page_t*)((uintptr_t)current + PAGE_SIZE);
        current = current->next;
    }
    current->next = NULL;  // Última página aponta para NULL
}

void* kalloc() 
{
    if (!allocator.free_list)
        return NULL;

    // Remover a primeira página da lista de páginas livres
    free_page_t* page = allocator.free_list;
    allocator.free_list = page->next;

    return (void*)page;
}

void kfree(void* page) 
{
    // Adicionar a página de volta à lista de páginas livres
    free_page_t* free_page = (free_page_t*)page;
    free_page->next = allocator.free_list;
    allocator.free_list = free_page;
}
