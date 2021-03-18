#include <stdio.h>

typedef struct {
	int aa;
	int bb;
	int cc;
	int dd;
}a;  // 16

typedef struct {
	char eee[256];
}c; //256

typedef struct {
	a st_1;  //16
	char aaa; //1
	char bbb; //1
	char ccc; //1
	int ddd; //4
	c st_2; //256 + 23 279
}__attribute__((packed)) b;

void main(void)
{
	b STRUCT;	
	printf("%lu\n",sizeof(STRUCT)); // 279


}

