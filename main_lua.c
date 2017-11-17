






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

#include "funchook.h"
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"



#define MAGIC_ADDR_H (0x12345678)

#define MAGIC_ADDR_L (0x22334411)

#define MAX_FUNS 100

void* g_code_begin_addr = NULL;

__thread lua_State* t_L = NULL;

typedef struct _interface_addr{

	int (*lua_pushnumber)(void*, double a);

	int (*lua_pcall)(void*, int, int, int);

	void* (*luaL_newstate)();

	void (*luaL_openlibs)();

	void (*luaL_dofile)(void*, const char*);

	void (*lua_getfield) (void *L, int idx, const char *k);

	int (*luaL_loadfile) (lua_State *L, const char *filename) ;
	
	void* hook_funaddr;

	void* (*get_thread_luastate)(struct _interface_addr* s);

	char m_notify_funname[16];

	void (*printf)(const char* fmt, ...);

	char m_output_str[256];
}interface_addr;


void* get_thread_luastate(interface_addr* s){
	
	if(t_L == NULL){
		
		t_L = s->luaL_newstate();

		printf("t_L=%p\n", t_L);
			
		luaL_openlibs(t_L);	

		 

		(s->luaL_loadfile(t_L, "hook_action.lua") || s->lua_pcall(t_L, 0, LUA_MULTRET, 0));
	}	
	
	return t_L;
}


typedef long (*LONG_F4_TYPE)(long a, long b,long c,long d);
LONG_F4_TYPE long_f4_arr[MAX_FUNS];
long hook_tpl_4(long a, long b, long c, long d){

	unsigned long tmp = 0;

	*(int*)((char*)&tmp + 4) = MAGIC_ADDR_H;

	*(int*)(&tmp) = ((unsigned int)MAGIC_ADDR_L);

	interface_addr* s = (interface_addr*)tmp;
	
	int magic_idx = 0;

	
	void* L = s->get_thread_luastate(s);
	
	s->lua_getfield(L, LUA_GLOBALSINDEX, s->m_notify_funname);
	s->lua_pushnumber(L, a);
	s->lua_pushnumber(L, b);
	s->lua_pushnumber(L, c);
	s->lua_pushnumber(L, d);
	
	s->lua_pcall(L, 4, 0, 0);
	return ((LONG_F4_TYPE)s->hook_funaddr)(a, b, c, d);
}


typedef void * (*luaM_realloc_type) (void *L, void *block, size_t osize, size_t nsize) ;

luaM_realloc_type g_hook_fun_ptr = NULL;

void *simple_hook_temp1 (void *L, void *block, size_t osize, size_t nsize)
{
	if(t_L == NULL){
		
		t_L = luaL_newstate();
			
		luaL_openlibs(t_L);	

		luaL_dofile(t_L, "hook_action.lua");

	}

	void* ret = g_hook_fun_ptr(L, block, osize, nsize);

	lua_getglobal(t_L, "hook_notify");

	lua_pushnumber(t_L, (long)pthread_self());
	lua_pushnumber(t_L, (long)block);
	lua_pushnumber(t_L, osize);
	lua_pushnumber(t_L, nsize);

	lua_pcall(t_L, 4, 0, 0);

	return ret;
		
}


int has_hook = 0;

void set_hook(lua_State *L){
	char*p = NULL;

	if(has_hook == 1)
		return;

	has_hook = 1;

	int cnt = sizeof(interface_addr*)/4;	 

	funchook_t *ft = funchook_create();	

	g_code_begin_addr = mmap(NULL, 4096, PROT_EXEC | PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS,-1, 0);

	interface_addr* s = (interface_addr*)g_code_begin_addr;

	s->lua_getfield = lua_getfield;
	s->luaL_loadfile = luaL_loadfile;
	s->lua_pushnumber = lua_pushnumber;
	s->luaL_openlibs = luaL_openlibs;
	s->lua_pcall = lua_pcall;
	s->luaL_newstate = luaL_newstate;	
	s->get_thread_luastate = get_thread_luastate;
	s->printf = printf;

	strcpy(s->m_notify_funname, "hook_notify");

 	mprotect(((unsigned long)hook_tpl_4 >> 12) << 12, 4096*2,  PROT_READ | PROT_EXEC | PROT_WRITE);

	g_hook_fun_ptr = (luaM_realloc_type)(void*)(long)lua_tonumber(L, -1);

	printf("g_code_begin_addr=%p\n", g_code_begin_addr);
	
	memcpy((char*)g_code_begin_addr +  sizeof(interface_addr), hook_tpl_4, 1024);

	//for(p = (char*)g_code_begin_addr +  sizeof(interface_addr); ; p++){

	for(p = (char*)hook_tpl_4; ; p++){
		if( (*(int*)p) == (MAGIC_ADDR_L)){

			printf("L=%p\n", p);

			cnt--;
			
			*(unsigned int*)p = (unsigned int)g_code_begin_addr;
			 
			
		}
		if( (*(int*)p) == (MAGIC_ADDR_H)){

			cnt--;
			printf("H=%p\n", p);
			*(unsigned int*)p = (unsigned int)(((unsigned long)g_code_begin_addr) >> 32);
			
		}

		if(cnt == 0)
			break;

	}


	 

	// ((LONG_F4_TYPE)(void*)((char*)g_code_begin_addr +  sizeof(interface_addr)))(L, 2, 3, 4);


	 //funchook_prepare(ft, (void**)&g_hook_fun_ptr, (char*)g_code_begin_addr +  sizeof(interface_addr));

	funchook_prepare(ft, (void**)&g_hook_fun_ptr, hook_tpl_4);

	  s->hook_funaddr = g_hook_fun_ptr;

	  funchook_install(ft, 0);
}


void __attribute__((constructor)) Init()
{


	///init_ctl_thread();





	lua_State *L =  luaL_newstate();
	
	luaL_openlibs(L);	

	lua_register(L, "set_hook", set_hook);
		
	luaL_dofile(L, "hook_init.lua");
	
	return 0;	
}



int ctl_thread(void* data){

	const char* sock_path = "/tmp/simplehook.sock";

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

	  write(client_sockfd, cmd, strlen(cmd));
	  
	  if(strncmp(cmd, "begin", 5) == 0){
			write(client_sockfd, message, strlen(message));
	  }else if(strncmp(cmd, "dump", 4) == 0){
			sprintf(message, "begin dump now!!\n");
			 
			write(client_sockfd, message, strlen(message));
			
			sprintf(message, "dump end!!\n");
			write(client_sockfd, message, strlen(message));
	  }else if(strncmp(cmd, "status", 6) == 0){

			
			 
			write(client_sockfd, message, strlen(message));	
	  }else if(strncmp(cmd, "show", 4) == 0){
			pos = 0;
			write(client_sockfd, buff, strlen(buff));
			
	  }else if(strncmp(cmd, "watchmethod=", 12) == 0){
			write(client_sockfd, message, strlen(message));	
	  }else if(strncmp(cmd, "watchsize=", 10) == 0){
			write(client_sockfd, message, strlen(message));	
	  	}
	  else{
			pos = 0;
			write(client_sockfd, buff, strlen(buff));	
	  }

	  /* close the socket */
	  close(client_sockfd);
	}

}

void init_ctl_thread(){
	pthread_t id_1;
	int ret=pthread_create(&id_1,NULL,(void  *) ctl_thread,NULL);
	if(ret != 0){
		 
		exit(0);
	}
}	



