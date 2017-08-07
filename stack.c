#include <stdio.h>
#include <stdlib.h>

int d;
int e;

int main(void)
{
	int a;
	int b;
	int c;
	int *p = (int*)malloc(sizeof(int));


	printf("a=%p\n",&a);
	printf("b=%p\n",&b);
	printf("c=%p\n",&c);
	printf("d=%p\n",&d);
	printf("e=%p\n",&e);
	printf("p=%p\n",p);


	return 0;
}
