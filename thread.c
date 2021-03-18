#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t thread1_mutex,thread2_mutex;

void thread_1();
void thread_2();
void call_1();
void call_2();
int i;

int main(void)
{
	pthread_t p_thread1,p_thread2;
	int a=100;
	int b=100;
	int status;


	pthread_mutex_init(&thread1_mutex,NULL);
	pthread_mutex_init(&thread2_mutex,NULL);


	pthread_create(&p_thread1, NULL,(void*) thread_1, (void *)&a);
	pthread_create(&p_thread2, NULL,(void*) thread_2, (void *)&b);

	pthread_join(p_thread1, (void**)&status);	
	printf("thread1=%d\n",status);
	pthread_join(p_thread2, (void**)&status);	
	printf("thread2=%d\n",status);

	pthread_mutex_destroy(&thread1_mutex);
	pthread_mutex_destroy(&thread2_mutex);
	return 0;
}

void thread_1(){
	while(1){
		call_1();
	}
}
void thread_2(){
	while(1){
		call_2();
	}
}

void call_1(){
	while(1){
		pthread_mutex_lock(&thread1_mutex);
		printf("%s\n",__FUNCTION__);
		pthread_mutex_unlock(&thread1_mutex);
		usleep(100000); // 0.01초
	}
}

void call_2(){
	while(1){
		pthread_mutex_lock(&thread1_mutex);
		printf("%s\n",__FUNCTION__);
		pthread_mutex_unlock(&thread1_mutex);
		usleep(100000);
	}
}

