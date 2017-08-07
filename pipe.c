#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
	int n, fd[2];
	char buf[255];
	 int pid;

	 if (pipe(fd) < 0)
	{
		perror("pipe error : ");
		exit(0);
	}

	// 파이프를 생성한다. 
	if ((pid = fork()) < 0)
	{
		perror("fork error : ");
		exit(0);
	}

	// 만약 자식프로세스라면 파이프에 자신의 PID 정보를 쓴다.
	else if (pid == 0)
	{
		close(fd[0]);
		while(1)
		{
			memset(buf, 0x00, 255);
			sprintf(buf, "Hello Mother Process. My name is %d\n", getpid());
			write(fd[1], buf, strlen(buf));
			sleep(1);
			}
		}

		// 만약 부모프로세스라면 파이프에서 데이타를 읽어들인다. 
		else
		{
			close(fd[1]);
			while(1)
			{
				printf("ppid=%d\n",getppid());
				printf("pid=%d\n",getpid());
				memset(buf, 0x00, 255);
				n = read(fd[0], buf, 255);
				fprintf(stderr, "%s", buf);
			}
		}
}
