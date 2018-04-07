#ifndef _TEXT_H
#define _TEXT_H

void draw_timed_text(void);
void start_timed_text(char*, unsigned int);
void draw_number(unsigned char, unsigned char, int);
void draw_bcd_number(unsigned char x, unsigned char y, long val);

#endif