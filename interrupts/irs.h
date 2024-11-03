#ifndef _IRS_H
#define _IRS_H

__attribute__((noreturn))
void exception_handler(void);

__attribute__((noreturn))
void keyboard_irq_handler(void);

__attribute__((noreturn))
void timer_irq_handler(void);

#endif