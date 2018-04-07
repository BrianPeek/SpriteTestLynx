#include <lynx.h>
#include <tgi.h>
#include "global.h"

extern unsigned char H0[];
extern unsigned char H1[];
extern unsigned char H2[];
extern unsigned char H3[];
extern unsigned char H4[];
extern unsigned char H5[];
extern unsigned char H6[];
extern unsigned char H7[];
extern unsigned char H8[];
extern unsigned char H9[];
extern unsigned char HA[];
extern unsigned char HB[];
extern unsigned char HC[];
extern unsigned char HD[];
extern unsigned char HE[];
extern unsigned char HF[];
extern unsigned char HG[];
extern unsigned char HH[];
extern unsigned char HI[];
extern unsigned char HJ[];
extern unsigned char HK[];
extern unsigned char HL[];
extern unsigned char HM[];
extern unsigned char HN[];
extern unsigned char HO[];
extern unsigned char HP[];
extern unsigned char HQ[];
extern unsigned char HR[];
extern unsigned char HS[];
extern unsigned char HT[];
extern unsigned char HU[];
extern unsigned char HV[];
extern unsigned char HW[];
extern unsigned char HX[];
extern unsigned char HY[];
extern unsigned char HZ[];
extern unsigned char Hexclam[];
extern unsigned char Hquote[];
extern unsigned char Hcolon[];

unsigned char *letters[] = {HA, HB, HC, HD, HE, HF, HG, HH, HI, HJ, HK, HL, HM, HN, HO, HP, HQ, HR, HS, HT, HU, HV, HW, HX, HY, HZ};
unsigned char *numbers[] = {H0, H1, H2, H3, H4, H5, H6, H7, H8, H9};
unsigned char *symbols[] = {Hquote, Hcolon, Hexclam};

static SCB_REHV_PAL ch = {
	BPP_1 | TYPE_NONCOLL,
	PACKED | REHV,
	0x20,
	0, 0,
	1, 0, 256, 256,
	{COLOR_WHITE}
};

void atari_drawtext(int x, int y, char *msg)
{
	ch.hpos = x;
	ch.vpos = y;
	ch.penpal[0] = tgi_getcolor();

	while (*msg)
	{
		char cha = *msg;

		if (cha >= 'A' && cha <= 'Z')
			ch.data = letters[cha - 'A'];
		else if(cha >= 'a' && cha <= 'z')
			ch.data = letters[cha - 'a'];
		else if(cha >= '0' && cha <= '9')
			ch.data = numbers[cha - '0'];
		else
		{
			switch(cha)
			{
				case '\"':
					ch.data = symbols[0];
					break;
				case ':':
					ch.data = symbols[1];
					break;
				case '!':
				case '-':
					ch.data = symbols[2];
					break;
			}
		}

		if(cha != ' ')
			tgi_sprite(&ch);

		ch.hpos += 4;
		++msg;
	}
}
