#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv[]){
	unsigned int i =0;
	pid_t pid;
	if((pid = fork())==0){
		for(i=0;i<UINT_MAX;i++){
		}
	}
	else{
		int status;
		waitpid(pid,&status,0);
	}


	return EXIT_SUCCESS;
}
