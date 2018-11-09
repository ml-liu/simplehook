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
#include "arpa/inet.h"
#include "BoundedPriQueue.h"

#define MAX_LOG_QUEUE_SIZE (1000000)
static FILE* g_log_file = NULL;
static QUEUE g_log_queue;
pthread_mutex_t g_log_mutex;
pthread_mutex_t g_backtrace_mutex;
static int  g_has_init = 0;

char log_file_name[255] = {0};

char flushPtr[1];

unsigned long long current_usecond(){

	struct timeval t;
		
	gettimeofday(&t, NULL);

	unsigned long long ret = t.tv_sec;

	ret *= 1000000;

	ret += (t.tv_usec);
	
	return ret;
}

unsigned long long current_msecond(){

	struct timeval t;
		
	gettimeofday(&t, NULL);

	unsigned long long ret = t.tv_sec;

	ret *= 1000;

	ret += (t.tv_usec/1000);
	
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

 
 __attribute((visibility("default"))) void ffi_flush_log(){
	 int ret = 0;
	 
	 do{
		 pthread_mutex_lock(&g_log_mutex);
		 ret = queue_push_without_alloc(&g_log_queue, flushPtr);
		 pthread_mutex_unlock(&g_log_mutex); 
	 
		 if(ret == 0)
			 break;
	 
		 printf("will sleep!!!!!");
		 usleep(100);
	 }while(ret == -1);

 }


void* log_thread(void* data){

	g_log_file = fopen(log_file_name,"w");

	#define LOG_BUFFER_CACHE_SIZE (1024*16*1024)

	static char s_buffer[LOG_BUFFER_CACHE_SIZE + LOG_BUFFER_CACHE_SIZE + 10] = {0};
	int cur_pos = 0;

	while(1){

		char* str = NULL;

		pthread_mutex_lock(&g_log_mutex);
		queue_pop_without_dealloc(&g_log_queue, (void**)&str);
		pthread_mutex_unlock(&g_log_mutex);


		if (NULL == str){
			usleep(10);
			continue;
		}


		int need_flush_cache = 0;
		int need_direct_write = 0;

		if(flushPtr == str){
			if(cur_pos > 0){
				fwrite(s_buffer, cur_pos, 1, g_log_file);
				cur_pos = 0;
			}

			fflush(g_log_file);
			continue;
		}

		if(strlen(str) >= (LOG_BUFFER_CACHE_SIZE)){
			need_flush_cache = 1;
			need_direct_write = 1;
		}

		if(cur_pos >= LOG_BUFFER_CACHE_SIZE){
			need_flush_cache = 1;
		}
		

		if(cur_pos > 0 && need_flush_cache){ 
			fwrite(s_buffer, cur_pos, 1, g_log_file);
			fflush(g_log_file);
			cur_pos = 0;
		}
		
	 
		if( need_direct_write ){
			fprintf(g_log_file, "%s", str);
			fflush(g_log_file);
		}else{
			cur_pos += sprintf(s_buffer + cur_pos, "%s", str);
		}

		free(str);

	}

	return NULL;

}

void log_init(const char* log_file){
	pthread_t id;

	if(0 != g_has_init)
		return;
	
	g_has_init = 1;

	if(log_file != NULL){
		strcpy(log_file_name, log_file);
	}else{
		strcpy(log_file_name, "simple.log");
	}

	pthread_mutex_init(&g_log_mutex, NULL);
	 

	queue_init(&g_log_queue, MAX_LOG_QUEUE_SIZE);
	queue_reserved(&g_log_queue,MAX_LOG_QUEUE_SIZE);

	pthread_create(&id, NULL, log_thread, NULL);	
}


__attribute((visibility("default"))) long  ffi_get_so_load_base(const char* so_path)
{

    char szPath[256] = {0};
    char szLines[1024] = {0};
    char *lpCh = NULL;
    long addr = 0;
    int nFind = 0;

    unsigned long long x1, x2;
    char  x3[256];

	void* base_addr = NULL;

    snprintf(szPath, sizeof(szPath), "/proc/self/maps");
    printf("%s", szPath);

    FILE *fp = fopen(szPath, "r");
    if (fp != NULL)
    {
        while (fgets(szLines, sizeof(szLines), fp))
        {
        	printf("%s\n", szLines);
            if (strstr(szLines, so_path))
            {
                x1=x2=0;
                memset(x3, 0, sizeof(x3));
                sscanf(szLines, "%llx-%llx %s %*s %*s %*s %*s", &x1,&x2,x3);
                printf("[get_so_load_base] Find %s addr: %llx %llx  %s\r\n", so_path, x1,x2,x3);

				if(strstr(x3, "x")){
					base_addr = (void*)x1;
					break;
				}
				
            }
        }

        fclose(fp);
    }
    else
    {
        printf("[get_so_load_base] fopen error\r\n");
    }

	return (long)base_addr;
}










__attribute((visibility("default")))  void ffi_log_out(char* str){

	int ret = 0;
	
	do{
		pthread_mutex_lock(&g_log_mutex);
		ret = queue_push_without_alloc(&g_log_queue, str);
		pthread_mutex_unlock(&g_log_mutex);	

		if(ret == 0)
			break;

		printf("will sleep!!!!!");
		usleep(100);
	}while(ret == -1);
}

__thread char* t_get_sock_info_ThreadBuf = NULL;
__thread char* t_get_peer_info_ThreadBuf = NULL;

__attribute((visibility("default")))  char* ffi_get_sock_info(int fd){

	struct sockaddr_in serv, guest;  
	char serv_ip[20] = {0};  

	socklen_t serv_len = sizeof(serv);	
	 
	getsockname(fd, (struct sockaddr *)&serv, &serv_len);  
	inet_ntop(AF_INET, &serv.sin_addr, serv_ip, sizeof(serv_ip));   

	if( NULL == t_get_sock_info_ThreadBuf)
		t_get_sock_info_ThreadBuf = malloc(30);

	sprintf(t_get_sock_info_ThreadBuf, "%s:%d", serv_ip, ntohs(serv.sin_port));

	return t_get_sock_info_ThreadBuf;
}

__attribute((visibility("default")))  char* ffi_get_peer_info(int fd){

	struct sockaddr_in serv, guest;  
	char serv_ip[20] = {0};  

	socklen_t serv_len = sizeof(serv);	
	 
	getpeername(fd, (struct sockaddr *)&serv, &serv_len);  
	inet_ntop(AF_INET, &serv.sin_addr, serv_ip, sizeof(serv_ip));   

	if( NULL == t_get_peer_info_ThreadBuf)
		t_get_peer_info_ThreadBuf = malloc(30);

	sprintf(t_get_peer_info_ThreadBuf, "%s:%d", serv_ip, ntohs(serv.sin_port));

	return t_get_peer_info_ThreadBuf;
}

__attribute((visibility("default"))) void ffi_sleep(int sec){

	sleep(sec);
}

__attribute((visibility("default"))) void ffi_usleep(int usec){

	usleep(usec);
}




unsigned long HashFn(void** stackData, int stackDataSize, StackInfoArray* m)
{
    int i;
    unsigned long long result = 0;

    for(i=0; i<stackDataSize; i++)
    {
        unsigned long long tmp = (unsigned long long)stackData[i];
        tmp = (tmp << 21) - (tmp << 3) - tmp;
        result ^= tmp;
    }
    return (unsigned long)(result);
}


void InitStackModule(){

	pthread_mutex_init(&g_backtrace_mutex, NULL);
	
}

StackInfoArray* NewStackInfoArray(int size, int stackLimit){

	StackInfoArray* m = (StackInfoArray*)malloc(sizeof(StackInfoArray));

	m->m_size = size;

	m->m_stackLimit = MAX_STACK_LIMIT;

	if(stackLimit > 0 && stackLimit < MAX_STACK_LIMIT)
		m->m_stackLimit = stackLimit;

	m->m_array = (StackInfoNode**)malloc(size * sizeof(StackInfoNode*));

	memset(m->m_array, 0, size * sizeof(StackInfoNode*));

	return m;
}


StackInfoNode* CurrentStackInfoNode(StackInfoArray* m, const char* luainfo){
	pthread_mutex_lock(&g_backtrace_mutex);	
    int stackId;
	unsigned long stackHash = 0;
    static void* currentStack[MAX_STACK_LIMIT];

	memset(currentStack, 0, sizeof(currentStack));
	
    int stackSize;

	int i;

	int flag = 0;

 	if(NULL != luainfo){
		stackSize = (strlen(luainfo) + sizeof(void*) - 1) / sizeof(void*);
		strncpy(currentStack, luainfo, sizeof(currentStack) - 1);
		flag = 1;
 	}else{
 	   	stackSize = backtrace(currentStack, m->m_stackLimit);
 	}
	stackHash = HashFn(currentStack,stackSize , m);

	stackId = stackHash%m->m_size;

	StackInfoNode** pn = &m->m_array[stackId];

	while(*pn != NULL){
		if((*pn)->m_flag == flag && (*pn)->m_stack_size == stackSize && (*pn)->m_hash == stackHash){

			for(i = 0; i < stackSize; i++){
				if((*pn)->m_stack_data[i] != currentStack[i])
					break;
			}

			if(i == stackSize){
				break;
			}
		}
		
		pn = &(*pn)->m_next;
	}

	if(NULL != *pn ){
		pthread_mutex_unlock(&g_backtrace_mutex);	 
		return *pn;
	}


	StackInfoNode* n = (StackInfoNode*)malloc(sizeof(StackInfoNode));

	memset(n, 0, sizeof(StackInfoNode));

	memcpy(n->m_stack_data, currentStack, stackSize*sizeof(void*));
	n->m_stack_size = stackSize;

	n->m_hash = stackHash;

	n->m_flag = flag;

	*pn = n;
	pthread_mutex_unlock(&g_backtrace_mutex);  
	return n;
	
}


void DumpStackInfoArray(StackInfoArray* m, const char* fileName){

	int i = 0, j = 0;

	FILE* f = fopen(fileName, "w");

    BOUNDED_PRI_QUEUE q;
    q = CreateBoundedPriQueue(400);	

	unsigned long long total_new_cnt = 0;
	unsigned long long total_del_cnt = 0;
	unsigned long long total_ref_cnt = 0;
	unsigned long long stackCnt = 0;

	unsigned long long total_alloc_size = 0;
	unsigned long long total_free_size  = 0;

	for(i = 0 ; i < m->m_size; i++){

		StackInfoNode* n = m->m_array[i];

		while(n != NULL){
			Enqueue(q, n->m_alloc_size-n->m_free_size, n);
			total_new_cnt += n->m_add_cnt;
			total_del_cnt += n->m_del_cnt;

			total_alloc_size += n->m_alloc_size;
			total_free_size += n->m_free_size;
			total_ref_cnt += (n->m_add_cnt-n->m_del_cnt);
			stackCnt ++;
			n = n->m_next;
		}
	}

   
    fprintf(f, "StackInfo stack count: %d, unfree size:%lld, total_alloc_size:%lld, total_free_size:%lld,  total add cnt: %lld, total del cnt:%lld, total ref cnt:%lld\n", (int)stackCnt, (total_alloc_size-total_free_size), total_alloc_size, total_free_size,total_new_cnt ,total_del_cnt ,total_ref_cnt);
    fprintf(f, " ****************************\n\n");

	
    StackInfoNode* n = (StackInfoNode*)Dequeue(q);
    while(n != NULL)
    {
		fprintf(f, "\nV1.1unfree size:%lld, alloc_size :%lld, free_size:%lld , ref count: %lld, total alloc count: %lld, total free count: %lld\n, ",(n->m_alloc_size - n->m_free_size), n->m_alloc_size, n->m_free_size,  (n->m_add_cnt-n->m_del_cnt),n->m_add_cnt,n->m_del_cnt);
		char** strings = backtrace_symbols(n->m_stack_data, n->m_stack_size);
		fprintf(f, "stack: \n");

		if(n->m_flag == 1){
			fprintf(f, "LUA:%s\n", (char*)n->m_stack_data);
			n = (StackInfoNode*)Dequeue(q);
			continue;
		}
		
		
		int stack_idx = 0;
		for(j=0; j< n->m_stack_size; j++)
		{
			Dl_info info;
			void* fun_addr = n->m_stack_data[stack_idx++];
			dladdr(fun_addr, &info);		
			int xx = (int)((unsigned long long )fun_addr - (unsigned long long )info.dli_fbase);
			fprintf(f, "## %s %d %p %p %s\n", info.dli_fname, xx,  fun_addr, info.dli_fbase  , strings[j]);
		} 

		
		free(strings);
        n = (StackInfoNode*)Dequeue(q);
    }


	fclose(f);

}


struct _ctl_thread_data{
	char m_sock_path[256];
	ctl_thread_handle_fun m_handle_fun;
};

static void* ctl_thread(void* data){
	struct _ctl_thread_data* d = (struct _ctl_thread_data*)data;

	const char* sock_path = d->m_sock_path;

	static char buff[4096];

	int pos = 0;
	
	unlink(sock_path);
	
	/* create a socket */
	int server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
	
	struct sockaddr_un server_addr;
	server_addr.sun_family = AF_UNIX;
	strcpy(server_addr.sun_path, sock_path);
	
	/* bind with the local file */
	bind(server_sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
	
	/* listen */
	listen(server_sockfd, 5);

	char message[255];

	char cmd[1024 + 1];
	
	char ch;
	int client_sockfd;
	struct sockaddr_un client_addr;
	socklen_t len = sizeof(client_addr);
	while(1)
	{
	
	  /* accept a connection */
	  client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_addr, &len);

	  if(client_sockfd == -1)
	  	continue;


	  memset(cmd, 0, sizeof(cmd));
	
	  /* exchange data */
	  read(client_sockfd, cmd, 1024);
	  
	  char* res = d->m_handle_fun(cmd);

	  write(client_sockfd, res, strlen(res));

	  free(res);
	  
	  /* close the socket */
	  close(client_sockfd);
	}

}	

void init_ctl_thread(const char* sockpath,ctl_thread_handle_fun handlefun){

	struct _ctl_thread_data* d = (struct _ctl_thread_data*)malloc(sizeof(struct _ctl_thread_data));

	strcpy(d->m_sock_path, sockpath);

	d->m_handle_fun = handlefun;

	pthread_t id;

	pthread_create(&id, NULL, ctl_thread, d);
}






