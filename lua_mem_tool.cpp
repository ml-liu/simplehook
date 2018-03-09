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
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

}


int log_out(const char* str){

	static unsigned long long s_begin = 0;

	int len = strlen(str) + 60;

	char* tmpbuf = (char*)malloc(strlen(str) + 60);

	unsigned long long tick = current_usecond() - s_begin;

	snprintf(tmpbuf, len - 1, "%d.%d [%d] %s", tick/1000000, (tick%1000000)/1000, pthread_self(), str );

	ffi_log_out(tmpbuf);

}



typedef struct _BLOCK_HDR
{
    long  magic;
	StackInfoNode* node;
} BLOCK_HDR;

#define MAGIC 0xA0BC0DEF


__thread StackInfoArray* t_StackInfoArr = NULL;


long long g_total_alloc_size = 0;

long long g_total_free_size = 0;

long long g_total_alloc_cnt = 0;

long long g_total_free_cnt = 0;

int g_has_started = 0;
int s_need_dump_idx = 0;


__thread int t_need_dump_idx = 0;
std::map<void*, void*> t_luaStateMap;


/************************** 
luajit的lj_alloc_f函数由于其特殊性，无法被HOOK(需要更新HOOK库，由于该情形较少发生，所以暂时不更新HOOK库，简单规避)
*******************************/

typedef void * (*lj_alloc_f_hook_type)(void *msp, void *ptr, size_t osize, size_t nsize);

static lj_alloc_f_hook_type s_mem_hook_addr = NULL;

__thread std::map<void*, int>* g_ptr_map;


typedef int (*lua_getstack_type)(lua_State *L, int level, lua_Debug *ar);
typedef int (*lua_getinfo_type)(lua_State *L, const char *what, lua_Debug *ar);
typedef int  (*lua_sethook_type)(void*, void*, int mask, int count);

lua_getstack_type s_lua_getstack = NULL;
lua_getinfo_type  s_lua_getinfo = NULL;
lua_sethook_type s_lua_sethook = NULL;


__thread char* t_luainfo = NULL;


static void callhook(lua_State *L, lua_Debug *ar){
	if(NULL ==  t_luainfo){
		t_luainfo = (char*)malloc(128);
	}
	s_lua_getinfo(L, "lnS", ar);
	snprintf(t_luainfo, 127, "%s:%d:%s", ar->source, ar->linedefined, ar->name); 
	t_luainfo[127] = '\0';
}


void *mem_hook_addr_wrap(void *msp, void *ptr, size_t osize, size_t nsize){

	if(NULL == g_ptr_map){
		g_ptr_map = new std::map<void*, int>;
	}

	void* ret =  s_mem_hook_addr(msp, ptr, osize, nsize);

	if(ptr != NULL){
		if(g_ptr_map->find(ptr) == g_ptr_map->end()){
			log_out("ERROR!!!!!!!!!!!!!!!!");
			sleep(10);
			return ret;
		}

		if((*g_ptr_map)[ptr] != osize){
			log_out("ERROR!!!!!!!!!!!!!!!! 2222222222");
			sleep(10);
			return ret;
		}

		g_ptr_map->erase(ptr);
	}

	if(ret != NULL){
		if(g_ptr_map->find(ret) != g_ptr_map->end()){
			log_out("ERROR!!!!!!!!!!!!!!!! 3333333333333");
			sleep(10);
			return ret;
		}

		(*g_ptr_map)[ret]= nsize;

	}

	return ret;
}




void *lj_alloc_f_hook(void *msp, void *ptr, size_t osize, size_t nsize){

	
	int  BLOCK_HEAD_SIZE = sizeof(BLOCK_HDR);
	(void)osize;
	char* ret_ptr = NULL;

	if(NULL == t_StackInfoArr){
		t_StackInfoArr = NewStackInfoArray(105708417 , 20);
	}



	if(t_need_dump_idx != s_need_dump_idx){
		char filename[100];

		sprintf(filename, "/tmp/luamem.%d.txt",(int)pthread_self());
		
		DumpStackInfoArray(t_StackInfoArr, filename);

		t_need_dump_idx = s_need_dump_idx;
	}
	
	 

	if(ptr != NULL){
		
		//char* tmpbuf = malloc(100);
		
		//sprintf(tmpbuf, "free ptr=%p, osize=%lld, nsize=%lld\n", (char*)ptr - BLOCK_HEAD_SIZE, osize, nsize);
		
		//ffi_log_out(tmpbuf);

		BLOCK_HDR* hdr = (BLOCK_HDR*)((char*)ptr - BLOCK_HEAD_SIZE);

		if(hdr->magic != MAGIC){
			log_out("lj_alloc_f_hook ptr magic error");
		}else{
			if(hdr->node != NULL){
				hdr->node->m_del_cnt++;
				hdr->node->m_free_size += osize;
			}
			__sync_fetch_and_add(&g_total_free_size, osize);
			__sync_fetch_and_add(&g_total_free_cnt, 1);
		}
	}
	
	if (nsize == 0) {
		if(ptr != NULL){
			  return mem_hook_addr_wrap(msp, (char*)ptr - BLOCK_HEAD_SIZE, osize + BLOCK_HEAD_SIZE , 0);
		}else{
			  return mem_hook_addr_wrap(msp,NULL, osize + BLOCK_HEAD_SIZE , 0);
		}
	} else if (ptr == NULL) {
	  ret_ptr = (char*)mem_hook_addr_wrap(msp, ptr, 0 , nsize + BLOCK_HEAD_SIZE);
	} else {
	  ret_ptr = (char*)mem_hook_addr_wrap(msp, (char*)ptr - BLOCK_HEAD_SIZE, osize + BLOCK_HEAD_SIZE , nsize + BLOCK_HEAD_SIZE);
	}


	__sync_fetch_and_add(&g_total_alloc_cnt, 1);
	__sync_fetch_and_add(&g_total_alloc_size, nsize);

	BLOCK_HDR* hdr = (BLOCK_HDR*)ret_ptr;

	hdr->magic = MAGIC;

	 

	if(g_has_started == 1){

		lua_Debug ar;

		char* luainfo = NULL;
		
		if(t_luaStateMap[msp] && s_lua_getstack(t_luaStateMap[msp], 0, &ar) == 1 ){
			luainfo = t_luainfo;
		}
		
		hdr->node = CurrentStackInfoNode(t_StackInfoArr, luainfo);
		hdr->node->m_alloc_size += nsize;
		hdr->node->m_add_cnt += 1;
	}else{
		hdr->node = NULL;
	}
	/*char* tmpbuf = malloc(100);
	
	sprintf(tmpbuf, "alloc ptr=%p, osize=%lld, nsize=%lld\n", ret_ptr, osize, nsize);
	
	ffi_log_out(tmpbuf);*/

	return ((char*)ret_ptr + BLOCK_HEAD_SIZE);

}





typedef void* (*lj_state_newstate_hook_type)(void* a, void* b);

lj_state_newstate_hook_type s_newstate_fun = NULL;

void* lj_state_newstate_hook(void* a, void* b)
{

	s_mem_hook_addr = (lj_alloc_f_hook_type)a;
	
	void* ret = 	s_newstate_fun((void*)lj_alloc_f_hook, b);

	t_luaStateMap[b] = ret;

	char* logbuf = (char*)malloc(100);
	
	sprintf(logbuf, "msp:%p, luastate is %p", b, ret);
	
	ffi_log_out(logbuf);

	lua_sethook(ret, (lua_Hook)callhook, LUA_MASKCALL | LUA_MASKRET, 0);

	return ret;
	
}







int hook_luajit_mem(lua_State* L){

	long new_fun_ptr  = (long)(lua_tonumber(L, -4));
	long getstack_ptr = (long)(lua_tonumber(L, -3));
	long getinfo_ptr  = (long)(lua_tonumber(L, -2));
	long sethook_ptr  = (long)(lua_tonumber(L, -1));	

	
	s_newstate_fun = (lj_state_newstate_hook_type)(void*)new_fun_ptr;
	s_lua_getstack = (lua_getstack_type)getstack_ptr;
	s_lua_getinfo = (lua_getinfo_type)getinfo_ptr;
	s_lua_sethook = (lua_sethook_type)sethook_ptr;

	funchook_t *fork_ft = funchook_create();
	funchook_prepare(fork_ft, (void**)&s_newstate_fun, (void*)lj_state_newstate_hook);
	funchook_install(fork_ft, 0);

	return 0;

}



static char* ctl_thread_handle(char* cmd){

	char* buff = (char*)malloc(1000);
	strcpy(buff, cmd);
	ffi_log_out(buff);

	char* res = (char*)malloc(1000);

	if(strncmp(cmd, "show", 4) == 0){
		sprintf(res, "unfree size:%lld, total_alloc_size:%lld, total_free_size:%lld, total_alloc_cnt:%lld, total_free_cnt:%lld\n",(g_total_alloc_size - g_total_free_size), g_total_alloc_size, g_total_free_size, g_total_alloc_cnt,g_total_free_cnt);
	}else if(strncmp(cmd, "dump", 4) == 0){
		s_need_dump_idx ++;
		sprintf(res, "s_need_dump_idx=%d", s_need_dump_idx);
	}else if(strncmp(cmd, "start", 5) == 0){
		g_has_started = 1;
		sprintf(res, "g_has_started=%d", g_has_started);
	}else{
		sprintf(res, "done!!!");
	}
	
	
	 
	return res;
}
int  get_so_load_base(lua_State* L)
{

	const char* so_path = lua_tostring(L, -1);

	long base_addr = ffi_get_so_load_base(so_path);

    lua_pushnumber(L, (double)(long)base_addr);

	return 1;
}


void __attribute__((constructor)) Init()
{
	pthread_t id_1;
	//signal(SIGTRAP, SIG_IGN);
	funchook_t *fork_ft = funchook_create();
	log_init(NULL);


	funchook_set_debug_file("funchook.log");
	void  (*RealFork)(void);
	RealFork = dlsym(RTLD_NEXT, "fork");

	funchook_prepare(fork_ft, (void**)&RealFork, fork);
	funchook_install(fork_ft, 0);	


	lua_State *L =  luaL_newstate();

	InitStackModule();
	
	luaL_openlibs(L);	
 	lua_register(L, "get_so_load_base", get_so_load_base);
	lua_register(L, "hook_luajit_mem", hook_luajit_mem);
	luaL_dofile(L, "hook.lua");

	init_ctl_thread("/tmp/luameme.sock", ctl_thread_handle);
	
	/*
	int ret=pthread_create(&id_1,NULL,(void  *) try_hook_thread,NULL);
	if(ret != 0){
		 
		exit(0);
	}*/

	 	
}



