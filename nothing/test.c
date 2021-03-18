#include <stdio.h>

int main(void)
{
	unsigned int a=60010;
	unsigned int b=564;
	unsigned int c=50000000;
	unsigned int r=0;
	 r= (a*b) % (c);
	printf("%d,%u\n",(a*b),r);



	return 0;
}

