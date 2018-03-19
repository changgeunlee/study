#include <stdio.h>
#include "main.h"
#ifndef chang
#define chang
#endif

int main()
{
	int imsi[3] = { 5, 3, 7};
	int *imsip;
	imsip = imsi;
	printf("%#010x %#010x %#010x\n",
			imsi, &imsi[0], imsip);

	return 0;
}
