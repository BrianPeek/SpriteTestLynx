#ifndef _GLOBAL_H
#define _GLOBAL_H

#include <lynx.h>
#include <6502.h>
#include <tgi.h>
#include <joystick.h>
#include <stdbool.h>
#include <conio.h>

#define SCREEN_W (160)
#define SCREEN_H (102)
#define LETTER_W (4)
#define LETTER_H (7)

extern void atari_drawtext(int,int,char*);

#define CLAMP(n,min,max) n = (n >= max ? max : (n <= min ? min : n))
#define WRAP(n,min,max) n = (n > max ? min : (n < min ? max : n))

#define SPR_W (8)
#define SPR_H (8)

typedef struct SPRITE {
	SCB_REHV_PAL scb;
	signed char hv;
	signed char vv;
} SPRITE;

#endif