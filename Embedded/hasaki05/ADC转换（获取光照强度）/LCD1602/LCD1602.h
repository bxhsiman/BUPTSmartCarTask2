#ifndef LCD1602_H
#define LCD1602_H

#include <reg52.h>
#include "public.h"

sbit RS=P2^6;
sbit RW=P2^5;
sbit E=P2^7;

void delay_ms(u16 time);
void LCD1602_write_cmd(u8 order);
void LCD1602_write_dat(u8 dat);
void LCD1602_init(void);
void LCD1602_display(u8 *num);

#define DB P0

#endif