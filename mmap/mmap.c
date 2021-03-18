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
#if _FILE_OFFSET_BITS == 64
#define fmt_off "%lld"
#else
#define fmt_off "%ld"
#endif

#define MSG_SIZE 23
#define MMAP_PAGE 1024 
#define LINE 500   // buff[LINE][CNT] =  500*24 = 12000
#define CNT 24

#define INPUT_FILENAME "input_file"
#define OUTPUT_FILENAME "output_file"

#define FILE_PATH "/home/cglee/study/wlogs/study/mmap"

typedef struct{
	int num;
	int name;
	int time;
	char msg[12];
}__attribute__((packed)) LOG_CONFIG;


void mmap_copy();

int main(int argc, char **argv)
{
	pthread_t p_thread[2];
	pthread_create(&p_thread[0],NULL,(void*)mmap_copy,NULL);

	pthread_join(p_thread[0],NULL);

}


void mmap_copy(){
	int fd=0;
	char *mmap_data=NULL;
	struct stat sb;
	LOG_CONFIG log_config;
	int flag= PROT_WRITE|PROT_READ;
	int i =0;
	char msg;
	char file_name[128]={0,};
	FILE *fd2 = NULL;
	int idx=0;
	char buff[LINE][CNT];

	//printf("log_config%p\nmmap_data=%p\n",&log_config,mmap_data);

	fd = open(INPUT_FILENAME,O_RDWR|O_CREAT,0664);
	if (fd >= 0){
		fstat(fd,&sb);
		//printf("sb.st_size = %lu\n",sb.st_size);
		if (( mmap_data = (char*)mmap(0,MMAP_PAGE,flag,MAP_SHARED,fd,0))== (char*)-1)
		{
			perror("mmap error");
			exit(1);
		}
		while(1){
	//		printf("log_config=%s\n",(char*)&log_config.name);
	//		memset(&log_config,0x00,MSG_SIZE);
	//		memcpy(&log_config,mmap_data,MSG_SIZE);
	//		printf("mmap[0]=%p\nmmap[24]=%p\n\n",&mmap_data[0],&mmap_data[24]);
	//		printf("mmap[0]=%c\nmmap[24]=%c\n\n",mmap_data[0],mmap_data[24]);

			/*
				버퍼에 쌓기
				-커널에서 바로 올려준 데이터를 안 쌓고 파일로 생성: 커널에서 데이터를 형식에 맞게 올려줘야 하는 번거로움 
				-일정 카운트 버퍼에 쌓고 파일로 생성: 버퍼 찰때까지 기다려야 함
			*/				
			

			/*
				파일 쓰기
				-mmap 에서 읽은 데이터 바로 파일로 생성
				-1초마다 쓰기: file i/o 상대적으로 적음, 버퍼 사용해야 함 
				-들어오는 대로 쓰기: file i/o 많을것으로 예상, 하지만 버퍼 안씀
			*/
			/*
				마지막 포인터 기억
			*/
			idx += sprintf(buff + idx , "%d,",mmap_data);

			sprintf(file_name,"%s/output_file",FILE_PATH);
			fd2 = fopen(file_name,"w+");
			//fwrite(mmap_data,1,MSG_SIZE,fd2);
			fclose(fd2);
			
			/*
				쓴 데이터 지우기 
			*/
			//memset(&log_config,0x00,MSG_SIZE);
			usleep(2000000);
		}
		munmap(mmap_data,MMAP_PAGE);
		close(fd);
	}
	else{
		perror("mmap error");
	} 
	munmap(mmap_data,MMAP_PAGE);
	close(fd);

}
