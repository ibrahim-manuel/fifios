#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <kernel/tty.h>
#include "keyboard.h"
#include "statuscode.h"
#include "keycode.h"

#define NUM_MAPPED_KEYS 89

bool pressed_keys[NUM_MAPPED_KEYS]; // Vector global para armazenar o estado de cada tecla
bool capslock_active = false;

int8_t keyboard_initialize(){ 
    /**
    * Este código implementa o procedimento de inicialização de teclado descrito pelo artigo do wiki.osdev.org: * https://wiki.osdev.org/%228042%22_PS/2_Controller, no entanto alguns passo são suprimidos, por se entender * que não sejam necessários para a implementação de um sistema simples para estudo de conceitos. 
    **/
    for(uint8_t i = 0; i < NUM_MAPPED_KEYS; i++){
        pressed_keys[i] = false;
    }
    disable_capslock();
    get_output_buffer_byte(); // esvazia o buffer de saida do ps2 lendo o byte contido no mesmo (se existir) e não processa-lo

    if(!controller_self_test())
        return CONTROLLER_SELF_TEST_FAILED;

    if(!interface_test())
        return INTERFACE_TEST_FAILED;

    enable_devices();

    if(!reset_device())
        return RESET_DEVICE_FAILED;

    if(!disable_capslock())
        return DISABLE_CAPSLOCK_FAILED;

    return OK;
}

bool enable_capslock(){
    return set_keyboard_leds(0x04);
}

bool disable_capslock(){
    return set_keyboard_leds(0x00);
}

void toggle_capslock(){
    capslock_active = !capslock_active;
    if (capslock_active)
        enable_capslock();
    else 
        disable_capslock();
}

uint8_t get_scancode_from_buffer(){
    return get_output_buffer_byte();
}

bool check_key_pressed_or_released(){
    return is_output_buffer_full();
}

bool is_key_pressed(int keycode) {
    if (keycode >= 0 && keycode < NUM_MAPPED_KEYS) {
        return pressed_keys[keycode];
    }
    return false;  // Retorna false se a tecla estiver fora do intervalo válido
}

void set_key_as_pressed(int keycode) {
    if (keycode >= 0 && keycode < NUM_MAPPED_KEYS) {
        pressed_keys[keycode] = true;
    }
}

void set_key_as_unpressed(uint8_t keycode){
    if (keycode >= 0 && keycode < NUM_MAPPED_KEYS) {
        pressed_keys[keycode] = false;
    }
}


