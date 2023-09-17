#include <STC89C5xRC.H>

void main()
{
	while(1)
	{
		if(P31 == 0)
			P20 = 0;
		else
			P20 = 1;
	}
}