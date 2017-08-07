#include <stdio.h>

void main()
{
	

#if 0
reset:
printf("1\n");

	while(1)
	{
		printf("while\n");
		usleep(1000000);
		goto reset;
	}

#endif
	while(1)
	{
		printf("while2\n");		
		usleep(1000000);
		goto reset;
	}
reset:
printf("2\n");

}
