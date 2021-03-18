#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void execute_reinit(int sig)
{
	printf("sig = %d\n",sig);
}

int main(void)
{
	FILE *fp;
	char buffer[] = {'x'};
	int state,i=0;
	struct sigaction act;

	act.sa_handler = execute_reinit;
	sigemptyset(&act.sa_mask);
	act.sa_flags=0;
	state = sigaction(SIGTTIN,&act,0);
	printf("state = %d\n",state);
/*
	while(1){
		if(state !=0)
			printf("state = %d\n",state);

		sleep(10);
	}
*/
	fp = fopen("test.txt","wa");
	while (1){
		printf("i = %d\n",i);
		fwrite(buffer,1,sizeof(buffer),fp);
		sleep(1);
		i++;
	}
	fclose(fp);
	return 0;

}
