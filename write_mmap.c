#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#define MMAP_FILENAME "test_mmap"
#define MMAP_PAGE 4096

typedef struct _node{
	char *data;
	struct _node *next;
}NODE;

typedef struct _list{
	NODE *cur;
	NODE *head;
	NODE *tail;
}LIST;


void mmap_write(char **argv);

int main(int argc, char **argv)
{
	pthread_t p_thread[2];	

	pthread_create(&p_thread[0],NULL,(void*)mmap_write,(char **)argv);

	pthread_join(p_thread[0],NULL);

	return 0;
}

void mmap_write(char **argv){
	int fd;
	char *file;
//	char *msg = "1500524275.995346,81,2,,167787099,0,0,0,53577,(null),167787009,0,0,0,3306,(n    ull),0,0,0,0,0,0,0,0,0,0,6,0,0,21,0,1,25,1,1,40,52,,,8,11,0,3,0,65534,,0,2,A    llow(Close) SPD[21] BYTE[52/40] PKT[1/1] [00:00:11],";
	int flag = PROT_WRITE|PROT_READ;
	char *msg;
	int i=0;

	NODE *node = (NODE *)malloc(sizeof(NODE));
	node->data = "1"; 
	strcpy(msg,node->data);

	fd = open(argv[1], O_RDWR | O_CREAT, 0664);

	if (fd >= 0){
		if ((file = ( char*)mmap(0,MMAP_PAGE,flag,MAP_SHARED,fd,0)) == (char*)-1)
		{
			perror("mmap error");
			exit(1);
		}

		for( i=0; i< 4096; i++)	
		{
			write(fd,msg,strlen(msg));
			printf("end file[%d] = %c,addr=%p,addr=%p\n",i,file[i],&file[0],&file[i]);
			usleep(1000000);
		}
	}
	munmap(file,MMAP_PAGE);
	close(fd);
}
