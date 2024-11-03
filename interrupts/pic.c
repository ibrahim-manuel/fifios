#include <stdint.h>
#include <stdbool.h>
#include <arch/i386/io.h>
#include <arch/i386/cpu.h>
#include "pic.h"

void PIC_sendEOI(uint8_t irq)
{
	if(irq >= 8)
		outb(PIC_EOI, PIC2_COMMAND);
	
	outb(PIC_EOI, PIC1_COMMAND);
}

void PIC_remap(int offset1, int offset2)
{
	uint8_t a1, a2;
	
	a1 = inb(PIC1_DATA);                        // save masks
	a2 = inb(PIC2_DATA);
	
	outb(ICW1_INIT | ICW1_ICW4, PIC1_COMMAND);  // starts the initialization sequence (in cascade mode)
	io_wait();
	outb(ICW1_INIT | ICW1_ICW4, PIC2_COMMAND);
	io_wait();
	outb(offset1, PIC1_DATA);                 // ICW2: Master PIC vector offset
	io_wait();
	outb(offset2, PIC2_DATA);                 // ICW2: Slave PIC vector offset
	io_wait();
	outb(4, PIC1_DATA);                       // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
	io_wait();
	outb(2, PIC2_DATA);                       // ICW3: tell Slave PIC its cascade identity (0000 0010)
	io_wait();
	
	outb(ICW4_8086, PIC1_DATA);               // ICW4: have the PICs use 8086 mode (and not 8080 mode)
	io_wait();
	outb(ICW4_8086, PIC2_DATA);
	io_wait();
	outb(a1, PIC1_DATA);   // restore saved masks.
	outb(a2, PIC2_DATA);
}

void pic_disable(void) {
    outb(0xff, PIC1_DATA);
    outb(0xff, PIC2_DATA);
}


void IRQ_set_mask(uint8_t IRQline) {
    uint16_t port;
    uint8_t value;

    if(IRQline < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        IRQline -= 8;
    }
    value = inb(port) | (1 << IRQline);
    outb(value, port);        
}

void IRQ_clear_mask(uint8_t IRQline) {
    uint16_t port;
    uint8_t value;

    if(IRQline < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        IRQline -= 8;
    }
    value = inb(port) & ~(1 << IRQline);
    outb(value, port);        
}