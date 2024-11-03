#include "irs.h"
#include "pic.h"
#include "../tty/tty.h"

void exception_handler() 
{
    int exception_id;
   __asm__ volatile ("movl %%eax, %0" : "=r"(exception_id));
}

void timer_irq_handler()
{
    PIC_sendEOI(0);
}

void keyboard_irq_handler()
{
    term_handle_key_event();
    PIC_sendEOI(1);
}

