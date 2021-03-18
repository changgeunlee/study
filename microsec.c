#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
int main()
{
struct timespec sCurNanoTimeVal;
int rtn, i;
 
	for(i=0; i<1000 ; i++){
	rtn = clock_gettime(CLOCK_REALTIME, &sCurNanoTimeVal);
	printf("[i:%06d] %ld %ld\n", i, sCurNanoTimeVal.tv_sec, sCurNanoTimeVal.tv_nsec);
 
	rtn = clock_gettime(CLOCK_REALTIME, &sCurNanoTimeVal);
	printf("[i:%06d] %ld %ld \n--\n", i, sCurNanoTimeVal.tv_sec, sCurNanoTimeVal.tv_nsec);
	}
 
	return 0;
}
