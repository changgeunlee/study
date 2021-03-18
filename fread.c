#include <stdio.h>
#include <stdlib.h>

int main(void)
{	
	FILE *fp;
	long lSize;
	char *buffer;
	size_t result;

	fp = fopen("test.txt","r");
	if (fp == NULL)
	{
		fputs("file rror",stderr);
		exit(1);
	}
	fseek(fp,0,SEEK_END);
	lSize= ftell(fp);
	rewind(fp);
	buffer = (char*)malloc(sizeof(char)*lSize);
	if(buffer==NULL)
	{
		fputs("file rror",stderr);
		exit(2);
	}
	result = fread(buffer,1,lSize,fp);
	if (result != lSize)
	{
		fputs("file rror",stderr);
		exit(3);
	}
	
	fclose(fp);
	free(buffer);
	return 0;
}


