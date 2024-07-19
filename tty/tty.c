#include <stdint.h>
#include <stdbool.h>
#include <kernel/video.h>
#include "../drivers/keyboard/keyboard.h"
#include "../drivers/keyboard/scancode.h"
#include "tty.h"

void term_handle_key_event()
{
	uint8_t scan_code = get_key_event();
	if (scan_code != 0x00)
    {

		if(scan_code == CAPSLOCK_PRESSED)
        {
			toggle_capslock();
			return;
		}

		if(scan_code == BACKSPACE_PRESSED)
        {
			video_erasechar();
			return;
		}
		
		char printable_char = get_printable_character(scan_code, capslock_active);
		if(printable_char != '\0')
        {
			video_putchar(printable_char);
			return;
		}
	}
}

void term_main()
{
	term_handle_key_event();
}