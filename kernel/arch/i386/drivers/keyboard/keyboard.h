/*
* 
* EM CASO DE DÚVIDAS E OMISSÕES CONSULTAR OS SEGUINTES ARTIGOS NO WIKI.OSDEV.ORG
* - https://wiki.osdev.org/PS/2_Keyboard
* - https://wiki.osdev.org/%228042%22_PS/2_Controller
* 
* OU O DATASHEET OFICIAL DA CONTROLADORA PS/2 8042
*
* NOTA: CCMD SIGNIFICA CONTROLER COMMAND E KCMD SIGNIFICA KEYBOARD COMMAND (NO PRIMEIRO CASO O COMANDO É ENVIADO * PARA A CONTROLADORA E NO SEGUNDO CASO O COMANDO É ENVIADO PARA O DISPOSITIVO QUE NESSE CASO É O TECLADO)
*
*/
#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include <stddef.h>
#include <arch/i386/io.h>
#include <arch/i386/ps2.h>
#include "scancode.h"

#define KCMD_SET_LEDS 0XED
#define KCMD_ECHO 0XEE
#define KCMD_GET_OR_SET_CURRENT_SCAN_CODE_SET 0XF0
#define KCMD_IDENTIFY_KEYBOARD 0XF2
#define KCMD_SET_TYPEMATIC_RAT_AND_DELAY 0XF3
#define KCMD_ENABLE_SCANNING 0XF4
#define KCMD_DISABLE_SCANNING 0XF5
#define KCMD_SET_DEFAULT_PARAMETERS 0xF6
#define KCMD_RESEND_LAST_BYTE 0xFE
#define KCMD_RESET_AND_START_SELFTESTING 0xFF
#define ACK 0xFA

extern bool capslock_active;

static char get_printable_character(uint8_t scancode, bool is_capslock_enabled);
static bool set_keyboard_leds(uint8_t code);
static bool reset_device();

int8_t keyboard_initialize();
uint8_t get_key_scancode();
void toggle_capslock();
bool enable_capslock();
bool disable_capslock();
bool check_key_pressed_or_released();

static char get_printable_character(uint8_t scancode, bool is_capslock_enabled) {
    switch (scancode) {
        case ONE_PRESSED: return '1';
        case TWO_PRESSED: return '2';
        case THREE_PRESSED: return '3';
        case FOUR_PRESSED: return '4';
        case FIVE_PRESSED: return '5';
        case SIX_PRESSED: return '6';
        case SEVEN_PRESSED: return '7';
        case EIGHT_PRESSED: return '8';
        case NINE_PRESSED: return '9';
        case ZERO_PRESSED: return '0';
        case MINUS_PRESSED: return '-';
        case EQUAL_PRESSED: return '=';
        case Q_PRESSED: return is_capslock_enabled ? 'Q' : 'q';
        case W_PRESSED: return is_capslock_enabled ? 'W' : 'w';
        case E_PRESSED: return is_capslock_enabled ? 'E' : 'e';
        case R_PRESSED: return is_capslock_enabled ? 'R' : 'r';
        case T_PRESSED: return is_capslock_enabled ? 'T' : 't';
        case Y_PRESSED: return is_capslock_enabled ? 'Y' : 'y';
        case U_PRESSED: return is_capslock_enabled ? 'U' : 'u';
        case I_PRESSED: return is_capslock_enabled ? 'I' : 'i';
        case O_PRESSED: return is_capslock_enabled ? 'O' : 'o';
        case P_PRESSED: return is_capslock_enabled ? 'P' : 'p';
        case LEFT_BRACKET_PRESSED: return '[';
        case RIGHT_BRACKET_PRESSED: return ']';
        case A_PRESSED: return is_capslock_enabled ? 'A' : 'a';
        case S_PRESSED: return is_capslock_enabled ? 'S' : 's';
        case D_PRESSED: return is_capslock_enabled ? 'D' : 'd';
        case F_PRESSED: return is_capslock_enabled ? 'F' : 'f';
        case G_PRESSED: return is_capslock_enabled ? 'G' : 'g';
        case H_PRESSED: return is_capslock_enabled ? 'H' : 'h';
        case J_PRESSED: return is_capslock_enabled ? 'J' : 'j';
        case K_PRESSED: return is_capslock_enabled ? 'K' : 'k';
        case L_PRESSED: return is_capslock_enabled ? 'L' : 'l';
        case SEMICOLON_PRESSED: return ';';
        case SINGLE_QUOTE_PRESSED: return '\'';
        case BACK_TICK_PRESSED: return '`';
        case Z_PRESSED: return is_capslock_enabled ? 'Z' : 'z';
        case X_PRESSED: return is_capslock_enabled ? 'X' : 'x';
        case C_PRESSED: return is_capslock_enabled ? 'C' : 'c';
        case V_PRESSED: return is_capslock_enabled ? 'V' : 'v';
        case B_PRESSED: return is_capslock_enabled ? 'B' : 'b';
        case N_PRESSED: return is_capslock_enabled ? 'N' : 'n';
        case M_PRESSED: return is_capslock_enabled ? 'M' : 'm';
        case COMMA_PRESSED: return ',';
        case PERIOD_PRESSED: return '.';
        case SLASH_PRESSED: return '/';
        case SPACE_PRESSED: return ' ';
        default: return '\0';  // caracter não imprimível
    }
}

static bool set_keyboard_leds(uint8_t code){
    uint8_t response;

    outb(KCMD_SET_LEDS, PORT_0x60);
    while(!(inb(PORT_0x64)&1));

    response = inb(PORT_0x60);
    if (response != ACK)
        return false;

    outb(code, PORT_0x60);
    while(!(inb(PORT_0x64)&1));
    
    response = inb(PORT_0x60);
    if(response != ACK)
        return false;

    return true;
}

static bool reset_device(){
    outb(KCMD_RESET_AND_START_SELFTESTING, PORT_0x60);

    while(!(inb(PORT_0x64)&1));

    uint8_t response = inb(PORT_0x60);

    if (response != 0xFA)
        return false;
    
    return true;
}
#endif