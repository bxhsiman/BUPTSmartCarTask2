#include <REGX52.H>
#include <INTRINS.H>
#include "Delay.h"

void Delay(unsigned char xms)		//@11.0592MHz
{
	unsigned char i, j;
	while(xms){
		_nop_();
	  _nop_();
	  _nop_();
	  i = 11;
  	j = 190;
  	do
  	{
  		while (--j);
	  } while (--i);
		xms--;
	}
}