#ifndef _CPU_H
#define _CPU_H 1
#include  "io.h"
static inline void io_wait(void)
{
    outb(0, 0x80);
}

static inline void freeze(void)
{
    __asm__ volatile ("hlt");
}

#endif