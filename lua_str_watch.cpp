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




typedef void * (*type_lua_str_new)(void *L, const char *str, size_t lenx);

type_lua_str_new s_new_str = NULL;

void * lua_str_new(void *L, const char *str, size_t lenx){

	log_out(str);

	return s_new_str(L, str, lenx);
}

int hook_newstr(lua_State* L){

	long fun_ptr  = (long)(lua_tonumber(L, -1));

	s_new_str = (type_lua_str_new)(void*)fun_ptr;

	funchook_t *fork_ft = funchook_create();
	funchook_prepare(fork_ft, (void**)&s_new_str, (void*)lua_str_new);
	funchook_install(fork_ft, 0);

	return 0;

}



static char* ctl_thread_handle(char* cmd){

	char* buff = (char*)malloc(1000);
	strcpy(buff, cmd);
	ffi_log_out(buff);

	char* res = (char*)malloc(1000);

	if(strncmp(cmd, "start", 5) == 0){
		sprintf(res, "willstart watch newstr");
	}else{
		strcpy(res, "unknown command!");	
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
	lua_register(L, "hook_newstr", hook_newstr);
	luaL_dofile(L, "hook.lua");

	init_ctl_thread("/tmp/luameme.sock", ctl_thread_handle);
	
	/*
	int ret=pthread_create(&id_1,NULL,(void  *) try_hook_thread,NULL);
	if(ret != 0){
		 
		exit(0);
	}*/

	 	
}



