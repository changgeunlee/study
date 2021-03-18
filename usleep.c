#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <stdint.h>
#include <stdint.h>
#include "usleep.h"

typedef enum {
	false,
	true
} bool;

int main(int argc, char *argv[])
{
	char buf[4096000];
	int i,j=0;
	int fd;
	struct stat sb;
	char *mmap_src=NULL;
	char *mmap_dst=NULL;
	int size;
	bool a=true,b=true;
	log_config_struct log_config;
	log_param_struct log_param;
	log_setting_struct set;

	printf("struct size = %d\n",sizeof(log_config));
	printf("struct size = %d\n",sizeof(log_param));
	printf("struct size = %d\n",sizeof(set));


reset:
	if ( b == true){
		while(1){
			if (a == true && i != 10){
				printf("i=%d\n",i);
				sleep(1);
				i++;
				continue;
			}
			b = false;
			printf("i=%d\n",i);
			sleep(1);
		}
	}
	else{
		b = true;
		printf("out\n");
	}
	goto reset;
/*
	fd = open(argv[1], O_RDWR);
	if (fd==-1){
		perror("open");
	}
	if(fstat(fd,&sb)  == -1){
		perror("fstat");
	}
#if 1
	if ((mmap_src =(char*)mmap(0,sb.st_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0)) == (char*)-1){
		perror("mmap");
	}
	mmap_dst = (char*)malloc(sb.st_size);
	memcpy(mmap_dst, mmap_src,sb.st_size);
	printf("%s\n",mmap_dst);
	printf("%dmb\n",(sb.st_size/1024)/1024);
	munmap(mmap_src,sb.st_size);
	close(fd);
	fd = open("bbbbb.txt", O_RDWR|O_CREAT,0644);
	write(fd,mmap_dst,sb.st_size+1);
	close(fd);
	free(mmap_dst);
	return 0;
#else

	read(fd,buf, sizeof(buf));
	printf("%s\n",buf);
	close(fd);
	fd = open("bbbbb.txt", O_RDWR | O_CREAT,0644);
	write(fd,buf,strlen(buf));
	close(fd);
	return 0;
#endif
*/
	return 0;
}
