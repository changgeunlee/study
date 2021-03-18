#include <stdio.h>

int main()
{
	int (*p)();
	p = main;
	printf("%p\n",p);
	return 0;
}
