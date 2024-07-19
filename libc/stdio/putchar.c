#include <stdio.h>
#include <kernel/video.h>

int putchar(int ic) 
{
	char c = (char) ic;
	video_write(&c, sizeof(c));
	return ic;
}
