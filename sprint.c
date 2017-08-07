#include <stdio.h>
#include <string.h>

#define buff_cnt 4500
#define max_str_cnt 350

char g_buff[buff_cnt+500][max_str_cnt]; // [0],[1],[2],[3],[4]
char g_cnt;

void insert_buff(char *buff);
void add_buff();

void main(void)
{
	int ret=0;
	char add_log_buff[512];
	int a=3;
	int b=5;
	int c=7;
	int i=0;
	memset(add_log_buff,0x00,sizeof(add_log_buff));
	for ( i=0;i<5;i++){
	ret+= sprintf(add_log_buff+ret,"%d,",b);
	ret+= sprintf(add_log_buff+ret,"%d,",a);
	ret+= sprintf(add_log_buff+ret,"%d\n",c);

	insert_buff(add_log_buff);
//	printf("%s\n",add_log_buff);
//	printf("i=%d,ret=%d,add_log_buff[%d]\n%s\n",i,ret,i, add_log_buff);
	}

}
void insert_buff(char *buff){
	int i=0;
	if ( (g_cnt) >= buff_cnt){  //  5
		add_buff();	
		g_cnt=0;
	}
	strncpy(g_buff[g_cnt++],buff,max_str_cnt);
}

void add_buff(){
	int i =0;	
	for( i=0;i<g_cnt;i++){
		printf("g_buff[%d]\n%s\n",i, g_buff[i]);
	}	
}
