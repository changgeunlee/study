#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define BUFF 512
int main(int argc, char** argv)
{
#if 0
	//char b="aasdfasdf";
	//char a[10]={'a','b','c','d','e','f','g','h','i','j'};
	char msg[256]="leechanggeun";
	char msg2[256]="kimbab";
	int i;
	char buff[BUFF];
	memset(&buff,0x00,BUFF);

	for(i=0; i<BUFF; i++){
		i=i*256;
		if ( i >= BUFF)
		{
			return 0;
		}
		memcpy(&buff[i],&msg,strlen(msg));
		printf("i=%d,%s\n",i,&buff[i]);
	}
	return 0;
	char buff[BUFF];
	int a,ret=0;
	int b =7;

	memset(buff,0x00,sizeof(buff));
	for(a=0;a<5;a++){   
	ret += sprintf(buff + ret, "%u,",a); // buff[0] buff[1] buff[2] 
	printf("buff[%d], %d, %d\n",a, ret, buff+ret);
	}

	printf("%d\n",~(b-1));

#else
	int i=0;
	double gap=0.0;
	clock_t sT=0,eT=0;
	printf("start\n");
	sT=clock();
	for(i=0;i<60000;i++){
	}
	eT=clock();
	printf("%f\n",(double)eT);
	gap = (double)(eT-sT)/CLOCKS_PER_SEC;
	printf("end %f초\n",gap);
//	usleep(1000000);

#endif

}
