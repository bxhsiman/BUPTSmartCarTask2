#include "LCD1602.h"
#include <intrins.h>
#include "public.h"


cmd_cursor_target_right=0x06;
cmd_cursor_hide=0x0C;
cmd_cursor_move_right=0x14;
cmd_cursor_move_left=0x10;
cmd_screen_clear=0x01;
cmd_mode=0x38;

void LCD1602_write_cmd(u8 order)
{
	RS=0;
	RW=0;
	E=0;
	DB=order;
	delay_ms(10);
	E=1;
	delay_ms(10);
	E=0;
}

void LCD1602_write_dat(u8 dat)
{
	RS=1;
	RW=0;
	E=0;
	DB=dat;
	E=1;
	delay_ms(10);
	E=0;
}

void delay_ms(u16 time)
{
	u16 i=time;
	for(i;i>0;i--);
}

void LCD1602_init(void)
{
	LCD1602_write_cmd(cmd_mode);
	LCD1602_write_cmd(cmd_cursor_target_right);
	LCD1602_write_cmd(cmd_cursor_hide);	
	LCD1602_write_cmd(cmd_screen_clear);
	delay_ms(20);
}

void LCD1602_display(u8 *str)
{
  LCD1602_write_cmd(cmd_screen_clear);
	delay_ms(120);
	while(*str!='\0')
	{
		LCD1602_write_dat(*str);
		str++;
	}
	delay_ms(20);
}	








