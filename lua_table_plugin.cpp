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
#include "netinet/in.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <map>
#include <string>
#include "common.h"
#include "netinet/in.h"
#include <unistd.h>
#include <fcntl.h>

extern "C" {
#include <sys/epoll.h>
#include "arpa/inet.h"
#include "funchook.h"

}
#include <map>
#include "speed_calculator.h"


std::map<void*, StackInfoNode*> g_tbl;

typedef int (*traversetable_type) (void *g, void *h);

traversetable_type s_traver = NULL;

int traversetable_hook (void *g, void *h){

	return s_traver(g, h);
}


typedef void (*markroot_type) (void *L);
markroot_type s_mark = NULL;

StackInfoArray* g_stack_arr = NULL;

void markroot_hook (void *L){
	return s_mark(L);
}

typedef void * (*luaH_new_type) (void *L, int narray, int nhash);
luaH_new_type s_new = NULL;

int s_need_dump = 0;

void *luaH_new_hook (void *L, int narray, int nhash) {

	static long this_thread = 0;

	static int has_dumped = 0;

	if(this_thread == 0){
		this_thread = pthread_self();
	}

	if(this_thread != pthread_self()){
		exit(0);
	}


	StackInfoNode* n = CurrentStackInfoNode(g_stack_arr);
	n->m_add_cnt++;

	if(s_need_dump == 1 ){
		DumpStackInfoArray(g_stack_arr, "stackinfo.log");
		s_need_dump = 0;
	}
		
	char* buff = (char*)malloc(60);

	void* ret = s_new(L, narray, nhash);
	sprintf(buff, "luaH_new_hook size=%d", (int)g_tbl.size());

	g_tbl[ret] = n;
	ffi_log_out(buff);

	return ret;
}


typedef void (*luaH_free_type) (void *L, void *t);
luaH_free_type s_free = NULL;
void luaH_free_hook (void *L, void *t){
	char* buff = (char*)malloc(60);
	static long this_thread = 0;

	if(this_thread == 0){
		this_thread = pthread_self();
	}

	if(this_thread != pthread_self()){
		exit(0);
	}

		
	if(g_tbl.find(t) == g_tbl.end()){
		sprintf(buff, "luaH_free_hook error!!!!");
	}else{
		sprintf(buff, "luaH_free_hook size=%d!!!!",(int) g_tbl.size());
		g_tbl[t]->m_del_cnt++;
		g_tbl.erase(t);
	}

	ffi_log_out(buff);	
	s_free(L, t);
}



 void lua_table_fun_hook( void* addr1, void* addr2, void* addr3,void* addr4){

	char* buff = (char*)malloc(280);

	sprintf(buff,"ssssss lua_table_fun_hook");
	ffi_log_out(buff);

	 
	 
	/*funchook_t *fork_ft = funchook_create();
	s_traver = addr1;
	funchook_prepare(fork_ft, (void**)&s_traver, traversetable_hook);
	funchook_install(fork_ft, 0);

	fork_ft = funchook_create();
	s_mark = addr2;
	funchook_prepare(fork_ft, (void**)&s_traver, markroot_hook);
	funchook_install(fork_ft, 0);
*/
	funchook_t *fork_ft = funchook_create();
	s_new = (luaH_new_type)(void*)addr3;
	funchook_prepare(fork_ft, (void**)&s_new, (void*)luaH_new_hook);
	funchook_install(fork_ft, 0);

	fork_ft = funchook_create();
	s_free = (luaH_free_type)(void*)addr4;
	funchook_prepare(fork_ft, (void**)&s_free, (void*)luaH_free_hook);
	funchook_install(fork_ft, 0);	


}


void* ctl_thread(void* data){

	char*	buff = (char*)malloc(60);

	sprintf(buff, "ctl_thread ");

	ffi_log_out(buff);	
}

pid_t fork(){
	printf("skip fork, just return 0...\n");
	return 0;
}


static char* ctl_thread_handle(char* cmd){

	char* buff = (char*)malloc(1000);
	strcpy(buff, cmd);
	ffi_log_out(buff);

	char* res = (char*)malloc(100);

	s_need_dump = 1;
	strcpy(res, "done");
	return res;
}

void __attribute__((constructor)) Init(){
	
	signal(SIGTRAP, SIG_IGN);

	g_stack_arr = NewStackInfoArray(105708417 , 20);

	char tbuff[256];

	sprintf(tbuff, "luatable.log.%d",(int) getpid());

	log_init(tbuff);

	char* buff = (char*)malloc(60);

	sprintf(buff, "Init ");

	ffi_log_out(buff);
	
	void  (*RealFork)(void);
	
	RealFork = dlsym(RTLD_NEXT, "fork");

	
	funchook_t *fork_ft = funchook_create();

	funchook_prepare(fork_ft, (void**)&RealFork, (void*)fork);
	funchook_install(fork_ft, 0);	


	long addr =	ffi_get_so_load_base("/root/muses/lib/libcore.so.1");

	lua_table_fun_hook((void*)addr , (void*)addr, (void*)(addr + 0x12b9e0) , (void*)(addr + 0x12ba70)  );	

	init_ctl_thread("/tmp/luatbl.sock", ctl_thread_handle);	
}



