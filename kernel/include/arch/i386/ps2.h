#ifndef _PS2_H
#define _PS2_H
#include <arch/i386/io.h>

#define PORT_0x60 0x60
#define PORT_0x64 0x64

#define CCMD_DISABLE_SECOND_PS2_PORT 0xA7
#define CCMD_ENABLE_SECOND_PS2_PORT 0xA8
#define CCMD_TEST_SECOND_PS2_PORT 0xA9
#define CCMD_TEST_PS2_CONTROLLER 0xAA
#define CCMD_TEST_FIRST_PS2_PORT 0xAB
#define CCMD_DIAGNOSTIC_DUMP 0xAC
#define CCMD_DISABLE_FIRST_PS2_PORT 0XAD
#define CCMD_ENABLE_FIRST_PS2_PORT 0xAE
#define CCMD_READ_CONTROLLER_INPUT_PORT 0xC0
#define CCMD_READ_CONTROLLER_OUTPUT_PORT 0xD0
#define CCMD_READ_CONTROLLER_BYTE 0x20
#define CCMD_WRITE_CONTROLLER_BYTE 0x60

/*#ifdef __cplusplus
extern "C" {
#endif

static inline void disable_devices();
static inline void enable_devices();
static inline void flush_output_buffer()
static bool controller_self_test();
static bool interface_test();

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#endif
*/
static inline void disable_devices(){
    outb(CCMD_DISABLE_FIRST_PS2_PORT, PORT_0x64);
    outb(CCMD_DISABLE_SECOND_PS2_PORT, PORT_0x64);
}

static inline void enable_devices(){
    outb(CCMD_ENABLE_FIRST_PS2_PORT, PORT_0x64);
    outb(CCMD_ENABLE_SECOND_PS2_PORT, PORT_0x64);
}

static inline bool is_output_buffer_full(){
    const uint8_t status_register = inb(PORT_0x64);
    return status_register & 1;
}

static uint8_t get_output_buffer_byte(){
    return inb(PORT_0x60);
}

static bool controller_self_test(){
    outb(CCMD_TEST_PS2_CONTROLLER, PORT_0x64);

    while(!(inb(PORT_0x64)&1));
    uint8_t response = inb(PORT_0x60);

    if (response != 0x55)
        return false;
    
    return true;
}

static bool interface_test(){
    outb(CCMD_TEST_FIRST_PS2_PORT, PORT_0x64);
    while(!(inb(PORT_0x64)&1));

    uint8_t response = inb(PORT_0x60);

    if (response != 0x00)
        return false;
    
    return true;
}
/*
#ifdef __cplusplus
}
#endif
*/
#endif