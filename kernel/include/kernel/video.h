#ifndef _KERNEL_VIDEO_H
#define _KERNEL_VIDEO_H

#include <stddef.h>

void init_video(void);
void video_putchar(char c);
void video_erasechar(void);
void video_write(const char* data, size_t size);
void video_writestring(const char* data);

#endif