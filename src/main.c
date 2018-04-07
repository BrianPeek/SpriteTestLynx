#include "global.h"
#include "text.h"
#include <stdlib.h>

extern unsigned char sprite[];

unsigned char lastJoy;
SPRITE *head;
SPRITE *end;
unsigned char refresh;
unsigned char sprctl0;
unsigned char stats = 1;
int count = 1;

SPRITE* init_sprite()
{
	SPRITE *spr = (SPRITE*)malloc(sizeof(SPRITE));

	spr->scb.sprctl0 = BPP_1 | (sprctl0 % 8);
	spr->scb.sprctl1 = PACKED | REHV;
	spr->scb.sprcoll = 0;
	spr->scb.data = sprite;
	spr->scb.hpos = rand() % 150;
	spr->scb.vpos = rand() % 92;
	spr->scb.hsize = 0x0100;
	spr->scb.vsize = 0x0100;
	spr->scb.penpal[0] = (rand()%14)+1;
	spr->hv = 1;
	spr->vv = 1;

	if(end)
	{
		end->scb.next = (char*)spr;
		end = spr;
	}

	return spr;
}

void delete_sprite()
{
	SPRITE *spr = head;
	while( ((SPRITE*)spr->scb.next)->scb.next != 0)
		spr = (SPRITE*)spr->scb.next;

	free(spr->scb.next);
	spr->scb.next = 0;
	end = spr;
}

void change_sprites()
{
	SPRITE *spr = head;
	while(true)
	{
		spr->scb.sprctl0 = BPP_1 | (sprctl0 % 8);
		if(spr->scb.next == 0)
			break;

		spr = (SPRITE*)spr->scb.next;
	}
}

void handle_input(unsigned char joy)
{
	if(JOY_UP(joy) && !JOY_UP(lastJoy))
	{
		++count;
		init_sprite();
	}

	if(JOY_DOWN(joy) && !JOY_DOWN(lastJoy) && count > 1)
	{
		--count;
		delete_sprite();
	}

	if(JOY_RIGHT(joy) && !JOY_RIGHT(lastJoy))
	{
		unsigned char i;
		for(i = 0; i < 5; i++)
		{
			++count;
			init_sprite();
		}
	}
	else if(JOY_LEFT(joy) && !JOY_LEFT(lastJoy) && count > 5)
	{
		unsigned char i;
		for(i = 0; i < 5; i++)
		{
			--count;
			delete_sprite();
		}
	}

	if(JOY_BTN_A(joy) && !JOY_BTN_A(lastJoy))
	{
		++sprctl0;
		change_sprites();
	}

	if(JOY_BTN_B(joy) && !JOY_BTN_B(lastJoy))
	{
		++refresh;
		switch(refresh%3)
		{
			case 0:
				tgi_setframerate(50);
				break;
			case 1:
				tgi_setframerate(60);
				break;
			case 2:
				tgi_setframerate(75);
				break;
		}
	}

	if(kbhit())
	{
		switch(cgetc())
		{
			case 'F': //flip
				tgi_flip();
				break;
			case '1': // opt1
				stats = !stats;
				break;
			case '2': // opt2
				break;
			case '3': // opt1 + opt2
				break;
			case '?': // all
				break;
			case 'R': // restart
				break;
			case 'P': // pause
				break;
		}
	}

	lastJoy = joy;
}

void main()
{
	tgi_install(&tgi_static_stddrv);
	joy_install(&joy_static_stddrv);
	tgi_init();
	tgi_setframerate(50);
	CLI();
	while (tgi_busy()) { }

	lynx_snd_init();
	lynx_snd_pause();

	head = init_sprite();
	end = head;

	tgi_setcolor(COLOR_BLUE);

	while(true)
	{
		unsigned char joy = joy_read(JOY_1);

		handle_input(joy);

		if(!tgi_busy())
		{
			SPRITE *ptr = head;

			tgi_clear();

			while(true)
			{
				if(ptr->scb.hpos == SCREEN_W - SPR_W)
					ptr->hv = -1;
				else if(ptr->scb.hpos == 0)
					ptr->hv = 1;

				if(ptr->scb.vpos == SCREEN_H - SPR_H)
					ptr->vv = -1;
				else if(ptr->scb.vpos == 0)
					ptr->vv = 1;

				ptr->scb.hpos += ptr->hv;
				ptr->scb.vpos += ptr->vv;

				if(ptr->scb.next == 0)
					break;

				ptr = (SPRITE*)ptr->scb.next;
			}

			tgi_sprite(head);

			if(stats)
			{
				draw_number(146,0,count);

				switch(refresh%3)
				{
					case 0:
						atari_drawtext(130,0,"50");
						break;
					case 1:
						atari_drawtext(130,0,"60");
						break;
					case 2:
						atari_drawtext(130,0,"75");
						break;
				}

				switch(sprctl0%8)
				{
					case 0:
						atari_drawtext(0,0,"BACKGROUND");
						break;
					case 1:
						atari_drawtext(0,0,"BACKNONCOLL");
						break;
					case 2:
						atari_drawtext(0,0,"BSHADOW");
						break;
					case 3:
						atari_drawtext(0,0,"BOUNDARY");
						break;
					case 4:
						atari_drawtext(0,0,"NORMAL");
						break;
					case 5:
						atari_drawtext(0,0,"NONCOLL");
						break;
					case 6:
						atari_drawtext(0,0,"XOR");
						break;
					case 7:
						atari_drawtext(0,0,"SHADOW");
						break;
				}
			}

			tgi_updatedisplay();
		}
	}
}
