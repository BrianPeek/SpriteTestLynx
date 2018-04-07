#include <stdlib.h>
#include "global.h"

unsigned char numberText[10];
unsigned int msgTimer = 0;
char *msg;

void draw_number(unsigned char x, unsigned char y, int val)
{
	itoa(val, numberText, 10);
	atari_drawtext(x, y, numberText);
}

void draw_bcd_number(unsigned char x, unsigned char y, long val)
{
	unsigned char i;
	for(i = 0; i < 6; i++)
		numberText[i] = val >> (20-(i*4)) + '0';
	numberText[6] = '\0';

	atari_drawtext(x, y, numberText);
}
