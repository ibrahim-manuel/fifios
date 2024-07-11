#ifndef _IO_H
#define _IO_H 1
 
#ifdef __cplusplus
extern "C" {
#endif

static inline unsigned char inb(unsigned short int port);
static inline void outb(unsigned char data, unsigned short int port);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#endif

static inline unsigned char inb(unsigned short int port){
    unsigned char data;
    asm volatile("inb %1, %0": "=a" (data) : "dN" (port));
    return data;
}

static inline void outb(unsigned char data, unsigned short int port){
    asm volatile ("outb %0, %1" :: "a" (data), "dN" (port));
}

#ifdef __cplusplus
}
#endif
 
#endif
