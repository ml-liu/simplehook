#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <dlfcn.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <execinfo.h>
#include <memory.h>
#include <stdarg.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include <dlfcn.h>
#include <assert.h>
#include <errno.h>
#include "queue.h"
#include "common.h"
#define MAX_LOG_QUEUE_SIZE (100000)
static FILE* g_log_file = NULL;
static QUEUE g_log_queue;
pthread_mutex_t g_log_mutex;
static int  g_has_init = 0;
unsigned long long current_usecond(){

	struct timeval t;
		
	gettimeofday(&t, NULL);

	unsigned long long ret = t.tv_sec;

	ret *= 1000000;

	ret += (t.tv_usec);
	
	return ret;
}



__attribute((visibility("default"))) double current_tick(){

	static unsigned long long s_begin = 0;

	if( 0 == s_begin ){
		s_begin = current_usecond();
	}

	return ((double)(current_usecond() - s_begin))/1000000;
}

 __attribute((visibility("default"))) long ffi_get_tid(){
     return (long)pthread_self();
 }


void* log_thread(void* data){

	g_log_file = fopen("simplehook.log","w");

	while(1){

		char* str = NULL;

		pthread_mutex_lock(&g_log_mutex);
		queue_pop_without_dealloc(&g_log_queue, (void**)&str);
		pthread_mutex_unlock(&g_log_mutex);

		if(str != NULL){
			
			fprintf(g_log_file, "%s\n", str);

			fflush(g_log_file);
			free(str);

			continue;
		}

		usleep(10);
	}

	return NULL;

}

void log_init(){
	pthread_t id;

	if(0 != g_has_init)
		return;
	
	g_has_init = 1;

	pthread_mutex_init(&g_log_mutex, NULL);
	 

	queue_init(&g_log_queue, MAX_LOG_QUEUE_SIZE);
	queue_reserved(&g_log_queue,MAX_LOG_QUEUE_SIZE);

	pthread_create(&id, NULL, log_thread, NULL);	
}

__attribute((visibility("default")))  void ffi_log_out(char* str){

	int ret = 0;
	
	do{
		pthread_mutex_lock(&g_log_mutex);
		ret = queue_push_without_alloc(&g_log_queue, str);
		pthread_mutex_unlock(&g_log_mutex);	

		usleep(100);
	}while(ret == -1);
}


