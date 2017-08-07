#include <stdio.h>

void hello()
{
	printf("hello,");
}

void numberToString(int n, char *buffer)
{
	sprintf(buffer,"%d",n);
}

int main()
{
	void (*fp1[1])();
	void (*fp2[1])(int,char *);

	char buffer[20];
	
	fp1[0] = hello;
	fp2[0] = numberToString;

	fp1[0]();
	fp2[0](100,buffer);
	printf("%s\n", buffer);
	return 0;
}	
