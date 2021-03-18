#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define BUF_SIZE 4096
#define ADD_SIZE 512
#define MMAP_PAGE 409600000
#define MMAP_FILENAME "test_mmap"

#define PATH "test_mmap_copied"

typedef struct{
	char msg[256];
}LOG_CONFIG;

void mmap_copied(char **argv);
int get_log(LOG_CONFIG log_config);
void insert_log(char* add_log);
void write_log();
void _write_log(char *filename);

int g_buff_cnt =0;
static char g_buff[5000][350];

int main(int argc, char **argv)
{
	pthread_t p_thread[2];
	pthread_create(&p_thread[0],NULL,(void*)mmap_copied,(char **)argv);

	pthread_join(p_thread[0],NULL);

}


void mmap_copied(char **argv){
	int fd,cnt=0;
	char *mmap_data;
	char *file;
	//char buff[BUF_SIZE];
	//char buff[BUF_SIZE]= "1500524275.995346,81,2,,167787099,0,0,0,53577,(null),167787009,0,0,0,3306,(null),0,0,0,0,0,0,0,0,0,0,6,0,0,21,0,1,25,1,1,40,52,,,8,11,0,3,0,65534,,0";
	struct stat sb;
	LOG_CONFIG log_config;
	int flag= PROT_WRITE|PROT_READ;
	double gap=0.0;
	clock_t sT=0,eT=0;
	int i =0;

	//memcpy(&log_config,buff,sizeof(buff));
	fd = open(argv[1],O_RDWR|O_CREAT,0664);
	if (fd >= 0){
		fstat(fd,&sb);
		//printf("sb.st_size = %lu\n",sb.st_size);
		if (( file = (char*)mmap(0,MMAP_PAGE,flag,MAP_SHARED,fd,0))== (char*)-1)
		{
			perror("mmap error");
			exit(1);
		}
		cnt=0;
		sT = clock();
		while(1){
			if (cnt > 100){
				eT = clock();
				gap = (double)(eT-sT)/CLOCKS_PER_SEC;
				printf("cnt=%d, end %f초\n",cnt,gap);
				cnt= 0;
				break;
			}
			/*
			if (cnt > 1000000){
				eT = clock();
				gap = (double)(eT-sT)/CLOCKS_PER_SEC;
				printf("cnt=%d, end %f초\n",cnt,gap);
				cnt= 0;
				break;
			}
			*/
			/* 10만건 만드는데 0.9초 걸림 
			write(fd,&log_config.msg,strlen(log_config.msg));
			*/
			memcpy(&log_config,file,sizeof(log_config));
			get_log(log_config);
			cnt++;
			printf("cnt=%d, end %f초\n",cnt,gap);
			//usleep(1000);
		}

#if 0
		for(i=0; i<4096; i++)
		{	
			if ( file[i] == NULL){
				usleep(1000000);
			}
			memcpy(buff,file,BUF_SIZE);
			printf("buff[%d]=%c\n",i,buff[i]);
			if ( buff[4096]==0){
		//	printf("before= %c\n",buff[4094]);
			memset(buff,0x00,BUF_SIZE);
		//	printf("after= %c\n",buff[4094]);
			}
			usleep(100000);
#endif
	}
	else
	{
		perror("file open error");
	} munmap(file,MMAP_PAGE);
	close(fd);

}


int get_log(LOG_CONFIG log_config)
{
	//printf("%s\n",__FUNCTION__);
	int ret=0;
	char add_log[ADD_SIZE];
	memset(add_log,0x00,sizeof(add_log));
	
	ret += sprintf(add_log+ret, "%s\n",log_config.msg);

	insert_log(add_log);
	return ret;
}

void insert_log(char *add_log)
{
	//printf("%s\n",__FUNCTION__);
	if (( g_buff_cnt + 1) >= 100 ) {
		write_log();
		g_buff_cnt=0;
	}
	strncpy(g_buff[g_buff_cnt++], add_log, 350);
}

void write_log(){
	//printf("%s\n",__FUNCTION__);
	char filename[128]={0,};
	sprintf(filename,"%s",PATH);
	_write_log(filename);

}
void _write_log(char *filename){
	//printf("%s\n",__FUNCTION__);
	FILE *fd = NULL;
	int i =0;
	fd = fopen(filename,"w");
	for( i=0; i<g_buff_cnt;i++){
		fprintf(fd,"%s",g_buff[i]);
	}
	fclose(fd);
}
