#ifndef XPT2046_H
#define XPT2046_H

#include "public.h"

void xpt2046_init(u8 cmd);
u16 xpt2046_read(void);
u16 xpt2046_adc(u8 cmd);

sbit DIN=P3^4;
sbit CS=P3^5;
sbit DCLK=P3^6;
sbit DOUT=P3^7;

#endif