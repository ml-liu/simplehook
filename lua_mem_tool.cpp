#include <sys/types.h>
#include <sys/socket.h>

#include <unistd.h>

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


struct LuaStateMemState{
	unsigned long long m_mem;
	void* m_state_ptr;
	unsigned long long    m_tid;
};

pthread_mutex_t g_global_lock;

#define MAX_LUA_STATE_COUNT 1000

int g_lua_lua_state_idx = 0;

LuaStateMemState g_lua_state_arr[MAX_LUA_STATE_COUNT];



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

unsigned long long g_total_alloc_lua_mem = 0;

unsigned long long g_total_free_lua_mem = 0;


static void callhook(lua_State *L, lua_Debug *ar){
	if(NULL ==  t_luainfo){
		t_luainfo = (char*)malloc(128);
	}
	s_lua_getinfo(L, "lnS", ar);
	snprintf(t_luainfo, 127, "%s:%d:%s", ar->source, ar->linedefined, ar->name); 
	t_luainfo[127] = '\0';
}







void *lj_alloc_f_hook(void *msp, void *ptr, size_t osize, size_t nsize){

	void* newPtr = NULL;

	int state_idx = (int)msp;


	if(g_lua_state_arr[state_idx].m_tid == 0){
		g_lua_state_arr[state_idx].m_tid = pthread_self();
	}else{
		if(g_lua_state_arr[state_idx].m_tid!= pthread_self()){
			exit(0);
		}
	}
	
	if(ptr != NULL){
		__sync_fetch_and_add(&g_total_free_lua_mem, osize);
		__sync_fetch_and_sub(&g_lua_state_arr[state_idx].m_mem, osize);
		
	}

	if(nsize != 0){
		__sync_fetch_and_add(&g_total_alloc_lua_mem, nsize);
		__sync_fetch_and_add(&g_lua_state_arr[state_idx].m_mem, nsize);
	}
	
	if (nsize == 0)
	{
		if(ptr != NULL){
		 
			free(ptr);
		}
	
		
		newPtr =  NULL;
	}
	else
	{
		
		newPtr = (void*)realloc(ptr, nsize);;
	}

	

	return newPtr;

}





typedef void* (*lj_state_newstate_hook_type)(void* a, void* b);

lj_state_newstate_hook_type s_newstate_fun = NULL;

void* lj_state_newstate_hook(void* a, void* b)
{

	s_mem_hook_addr = (lj_alloc_f_hook_type)a;

	int cur_idx = __sync_fetch_and_add(&g_lua_lua_state_idx, 1);

	if(cur_idx >= MAX_LUA_STATE_COUNT){
		exit(-1);
	}
	
	void* ret = 	s_newstate_fun((void*)lj_alloc_f_hook, (void*)cur_idx);

	g_lua_state_arr[cur_idx].m_state_ptr = ret;

	//t_luaStateMap[b] = ret;

	char* logbuf = (char*)malloc(100);
	
	sprintf(logbuf, "msp:%p, luastate is %p", b, ret);
	
	ffi_log_out(logbuf);

	//s_lua_sethook(ret, (lua_Hook)callhook, LUA_MASKCALL | LUA_MASKRET, 0);

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
	int i = 0;

	int cur_pos = 0;

	char* res = (char*)malloc(1024*10240);

	if(strncmp(cmd, "show", 4) == 0){
		sprintf(res, "unfree size:%lld, total_alloc_size:%lld, total_free_size:%lld, total_alloc_cnt:%lld, total_free_cnt:%lld\n",(g_total_alloc_size - g_total_free_size), g_total_alloc_size, g_total_free_size, g_total_alloc_cnt,g_total_free_cnt);
	}
	else if(strncmp(cmd, "luamem", 6) == 0){
		cur_pos += sprintf(res, "lua alloc:%llu lua free:%llu lua unfree:%llu\n",g_total_alloc_lua_mem,g_total_free_lua_mem, g_total_alloc_lua_mem-g_total_free_lua_mem);

		std::map<unsigned long long, unsigned long long> s;
		
		for(i = 0; i < g_lua_lua_state_idx; i++){
			cur_pos += sprintf(res + cur_pos, "[%llu][%p] luamem:%llu\n", g_lua_state_arr[i].m_tid, g_lua_state_arr[i].m_state_ptr, g_lua_state_arr[i].m_mem);

			s[g_lua_state_arr[i].m_tid] += g_lua_state_arr[i].m_mem;
		}	

		for(std::map<unsigned long long, unsigned long long>::iterator it = s.begin(); it != s.end(); ++it)
			{
				cur_pos += sprintf(res + cur_pos, "[%llu] luamem:%llu\n", it->first, it->second);
			}
		
	}
	else if(strncmp(cmd, "dump", 4) == 0){
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

	memset(g_lua_state_arr, 0, sizeof(g_lua_state_arr));


	funchook_set_debug_file("funchook.log");
	void  (*RealFork)(void);
	RealFork = dlsym(RTLD_NEXT, "fork");

	funchook_prepare(fork_ft, (void**)&RealFork, fork);
	funchook_install(fork_ft, 0);	


	lua_State *L =  luaL_newstate();

	InitStackModule();
	
	luaL_openlibs(L);	
 	lua_register(L, "get_so_load_base", get_so_load_base);
	lua_register(L, "hook_lua_mem", hook_luajit_mem);
	luaL_dofile(L, "hook.lua");

	init_ctl_thread("/tmp/luameme.sock", ctl_thread_handle);
	
	/*
	int ret=pthread_create(&id_1,NULL,(void  *) try_hook_thread,NULL);
	if(ret != 0){
		 
		exit(0);
	}*/

	 	
}



