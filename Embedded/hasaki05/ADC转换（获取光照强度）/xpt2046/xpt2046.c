#include "xpt2046.h"
#include "intrins.h"

void xpt2046_init(u8 cmd)
{
	u8 i;
	
	DCLK=0;
	_nop_();
	for(i=0;i<8;i++)
	{
		DIN = cmd >> 7;
		cmd <<= 1;
		DCLK=0;
		_nop_();
		DCLK=1;
		_nop_();
	}
}

u16 xpt2046_read(void)
{
	u8 i;
	
	u16 xpt_data=0;
	DCLK=0;
	_nop_();
	for(i=0;i<12;i++)
	{
		DCLK=1;
		_nop_();
		DCLK=0;
		xpt_data |= DOUT;
    xpt_data <<= 1;		
	}
	return xpt_data;
}

u16 xpt2046_adc(u8 cmd)
{
	u16 output;
	DCLK=0;
	CS=0;
	xpt2046_init(cmd);
	DCLK=0;
	_nop_();
	DCLK=1;
	output=xpt2046_read();
	CS=1;
  return output;	
}