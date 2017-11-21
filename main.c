






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
#include "funchook.h"
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

#include "avcall.h"

#include "callback.h"
char g_sig[256] = {0};
static lua_State* s_process_luaState = NULL;
#include "queue.h"
#define MAX_LOG_QUEUE_SIZE (100000)
static FILE* g_log_file = NULL;
static QUEUE g_log_queue;
pthread_mutex_t g_log_mutex;


void* log_thread(void* data){

	g_log_file = fopen("simplehook.log","w");

	while(1){

		char* str = NULL;

		pthread_mutex_lock(&g_log_mutex);
		queue_pop_without_dealloc(&g_log_queue, (void**)&str);
		pthread_mutex_unlock(&g_log_mutex);

		if(str != NULL){
			
			fprintf(g_log_file, "%s\n", str);

			free(str);

			continue;
		}

		usleep(10);
	}

	return NULL;

}

void log_init(){
	pthread_t id;


	pthread_mutex_init(&g_log_mutex, NULL);
	 

	queue_init(&g_log_queue, MAX_LOG_QUEUE_SIZE);
	queue_reserved(&g_log_queue,MAX_LOG_QUEUE_SIZE);

	pthread_create(&id, NULL, log_thread, NULL);	
}


int log_out(lua_State* L){

	const char* str = lua_tostring(L, -1);

	char* tmpbuf = malloc(strlen(str) + 1);

	strcpy(tmpbuf, str);

	pthread_mutex_lock(&g_log_mutex);
	queue_push_without_alloc(&g_log_queue, tmpbuf);
	pthread_mutex_unlock(&g_log_mutex);	

}

unsigned long long current_usecond(){

	struct timeval t;
		
	gettimeofday(&t, NULL);

	unsigned long long ret = t.tv_sec;

	ret *= 1000000;

	ret += (t.tv_usec);
	
	return ret;
}


int get_tid(lua_State* L){

   lua_pushnumber(L, (long)pthread_self());

   return 1;

}

int get_pid(lua_State* L){

   lua_pushnumber(L, (long)getpid());

   return 1;

}


int  get_so_load_base(lua_State* L)
{

	const char* so_path = lua_tostring(L, -1);


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

    lua_pushnumber(L, (double)(long)base_addr);

	return 1;
}



struct ffctx{	const char* sig;	void* to; const char* luafunction;};

#define LUA_PUSH(a) do{ \
	luaparams++;\
	lua_pushnumber(t_L, (double)(a)); \
	}while(0);


int get_current_stack(lua_State* L);


#define MAGIC_ADDR_H (0x12345678)

#define MAGIC_ADDR_L (0x22334411)

#define STACK_LIMIT 30

#define MAX_FUNS 100
void* g_has_hook_addr_array[MAX_FUNS] = {0};
int   g_hook_idx = 0;

__thread lua_State* t_L = NULL;

char g_lua_fun_name[256];

static void wrap_function(void* data, va_alist alist){
	union fun_ret_ty {
		char c;
		signed char b;
		unsigned char B;
		short h;
		unsigned H;
		int i;
		unsigned int I;
		long l;
		unsigned long L;
		long long q;
		unsigned long long Q;
		float f;
		double d;
		void* P;
	} ret;

	int luaparams = 0;

	if(t_L == NULL){

		if(s_process_luaState != NULL){
			t_L = s_process_luaState;		
		}else{
			t_L =  luaL_newstate();
			luaL_openlibs(t_L);	
		}
		
		lua_register(t_L,"get_current_stack", get_current_stack);
		lua_register(t_L, "get_so_load_base", get_so_load_base);
		lua_register(t_L, "get_tid", get_tid);
		lua_register(t_L, "get_pid", get_pid);
		lua_register(t_L, "log_out", log_out);
		extern void add_lua_interface(lua_State* L);
	
		add_lua_interface(t_L);
		luaL_loadfile(t_L, "hook.lua") ;
		lua_pcall(t_L, 0, LUA_MULTRET, 0);		
	}	
	
	
	
	struct ffctx* ctx = (struct ffctx*) data;

	lua_getglobal(t_L, ctx->luafunction);
	const char* sig = ctx->sig;
	void* to = ctx->to;
	int rt = *sig++;
	int tt;
//precall
	//printf("======= [wrapped] calling %p(%s) luafunction:%s\n", to, ctx->sig, ctx->luafunction);
	av_alist vlist;
	switch(rt){
		case 'v':
			va_start_void(alist);
			av_start_void(vlist, to);
			break;
		case 'c':
			va_start_char(alist);
			av_start_char(vlist, to, &ret.c);
			break;
		case 'b':
			va_start_schar(alist);
			av_start_schar(vlist, to, &ret.b);
			break;
		case 'B':
			va_start_uchar(alist);
			av_start_uchar(vlist, to, &ret.B);
			break;
		case 'h':
			va_start_short(alist);
			av_start_short(vlist, to, &ret.h);
			break;
		case 'H':
			va_start_ushort(alist);
			av_start_ushort(vlist, to, &ret.H);
			break;
		case 'i':
			va_start_int(alist);
			av_start_int(vlist, to, &ret.i);
			break;
		case 'I':
			va_start_uint(alist);
			av_start_uint(vlist, to, &ret.I);
			break;
		case 'l':
			va_start_long(alist);
			av_start_long(vlist, to, &ret.l);
			break;
		case 'L':
			va_start_ulong(alist);
			av_start_ulong(vlist, to, &ret.L);
			break;
		case 'q':
			va_start_longlong(alist);
			av_start_longlong(vlist, to, &ret.q);
			break;
		case 'Q':
			va_start_ulonglong(alist);
			av_start_ulonglong(vlist, to, &ret.Q);
			break;
		case 'f':
			va_start_float(alist);
			av_start_float(vlist, to, &ret.f);
			break;
		case 'd':
			va_start_double(alist);
			av_start_double(vlist, to, &ret.d);
			break;
		case 'P':
			va_start_ptr(alist, void*);
			av_start_ptr(vlist, to, void*, &ret.P);
			break;
		default:
			assert(0);
			
	}
	while ((tt = *sig++)){
		switch(tt){
			case 'c':
				{char arg = va_arg_char(alist);
				av_char(vlist, arg);LUA_PUSH(arg);}
				break;
			case 'b':
				{signed char arg = va_arg_schar(alist);
				av_schar(vlist, arg);LUA_PUSH(arg);}
				break;
			case 'B':
				{unsigned char arg = va_arg_uchar(alist);
				av_uchar(vlist, arg);LUA_PUSH(arg);}
				break;
			case 'h':
				{short arg = va_arg_short(alist);
				av_short(vlist, arg);LUA_PUSH(arg);}
				break;
			case 'H':
				{unsigned short arg = va_arg_ushort(alist);
				av_ushort(vlist, arg);LUA_PUSH(arg);}
				break;
			case 'i':
				{int arg = va_arg_int(alist);
				av_int(vlist, arg);LUA_PUSH(arg);}
				break;
			case 'I':
				{unsigned int arg = va_arg_uint(alist);
				av_uint(vlist, arg);LUA_PUSH(arg);}
				break;
			case 'l':
				{long arg = va_arg_long(alist);
				av_long(vlist, arg);LUA_PUSH(arg);}
				break;
			case 'L':
				{unsigned long arg = va_arg_ulong(alist);
				av_ulong(vlist, arg);LUA_PUSH(arg);}
				;
				break;
			case 'q':
				{long long arg = va_arg_longlong(alist);
				av_longlong(vlist, arg);LUA_PUSH(arg);}
				break;
			case 'Q':
				{unsigned long long arg = va_arg_ulonglong(alist);
				av_ulonglong(vlist, arg);LUA_PUSH(arg);}
				break;
			case 'f':
				{float arg = va_arg_float(alist);
				av_float(vlist, arg);LUA_PUSH(arg);}
				break;
			case 'd':
				{double arg = va_arg_double(alist);
				av_double(vlist, arg);LUA_PUSH(arg);}
				break;
			case 'P':
				{void* xxx = va_arg_ptr(alist, void*);
				av_ptr(vlist, void* , xxx);LUA_PUSH((long)xxx);}
				break;
			default:
				assert(0);
		}
	}


	unsigned long long now = current_usecond();
	av_call(vlist);	
	unsigned long long elaps = current_usecond() - now;
	

	

	switch(rt){
		case 'v':
			va_return_void(alist);
			break;
		case 'c':
			va_return_char(alist, ret.c);
			LUA_PUSH(ret.c);
			break;
		case 'b':
			va_return_schar(alist, ret.b);
			LUA_PUSH(ret.b);
			break;
		case 'B':
			va_return_uchar(alist, ret.B);
			LUA_PUSH(ret.B);			
			break;
		case 'h':
			va_return_short(alist, ret.h);
			LUA_PUSH(ret.h);			
			break;
		case 'H':
			va_return_ushort(alist, ret.H);
			LUA_PUSH(ret.H);			
			break;
		case 'i':
			va_return_int(alist, ret.i);
			LUA_PUSH(ret.i);			
			break;
		case 'I':
			va_return_uint(alist, ret.I);
			LUA_PUSH(ret.I);			
			break;
		case 'l':
			va_return_long(alist, ret.l);
			LUA_PUSH(ret.l);			
			break;
		case 'L':
			va_return_ulong(alist, ret.L);
			LUA_PUSH(ret.L);			
			break;
		case 'q':
			va_return_longlong(alist, ret.q);
			LUA_PUSH(ret.q);			
			break;
		case 'Q':
			va_return_ulonglong(alist, ret.Q);
			LUA_PUSH(ret.Q);			
			break;
		case 'f':
			va_return_float(alist, ret.f);
			LUA_PUSH(ret.f);			
			break;
		case 'd':
			va_return_double(alist, ret.d);
			LUA_PUSH(ret.d);			
			break;
		case 'P':
			va_return_ptr(alist, void*, ret.P);
			LUA_PUSH((long)ret.P);			
			break;
		default:
			assert(0);
			
	}

	LUA_PUSH(elaps);

	lua_pcall(t_L, luaparams, 0, 0);
//postcall
	
	//printf("======= [wrapped] return from %p(%s)\n", to, ctx->sig);
}


void* alloc_wrap(void* func, const char* sig){
	callback_t ret;
	struct ffctx* ctx = (struct ffctx*)malloc(sizeof(struct ffctx));
	ctx->sig = strdup(g_sig);
	ctx->to = func;
	ctx->luafunction = strdup(g_lua_fun_name);
	ret = alloc_callback(&wrap_function, ctx);
	return (void*) ret;
}

void free_wrap(void* wrap){
	callback_t cb = (callback_t) wrap;
	struct ffctx* ctx = (struct ffctx*) callback_data(cb);
	free_callback((callback_t)wrap);
	free((void*)ctx->sig);
	free(ctx);
}


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

	char m_notify_funname[256];

	void (*printf)(const char* fmt, ...);

	void  (*lua_pushlightuserdata) (void *L, void *p);
}interface_addr;





void* get_thread_luastate(interface_addr* s){
	
	if(t_L == NULL){
		
		t_L = s->luaL_newstate();

		printf("t_L=%p\n", t_L);
			
		luaL_openlibs(t_L);	

		lua_register(t_L,"get_current_stack",get_current_stack);

		(s->luaL_loadfile(t_L, "hook.lua") || s->lua_pcall(t_L, 0, LUA_MULTRET, 0));
	}	
	
	return t_L;
}

int set_hook(lua_State *L){
	
	char*p = NULL;
	

	void* origion_hook_fun_addr = (void*)(long)lua_tonumber(L, -3);


	printf("set_hook origion_hook_fun_addr=%p\n", origion_hook_fun_addr);
	
	const char* sig = lua_tostring(L, -2);
	const char* lua_notify_fun_name = lua_tostring(L, -1);

	int i = 0;

	
	for(i = 0; i < MAX_FUNS; i++){
		if(g_has_hook_addr_array[i] == origion_hook_fun_addr)
			return;
	}

	if(g_hook_idx == MAX_FUNS - 1){
		return;
	}
	
	g_has_hook_addr_array[g_hook_idx++] = origion_hook_fun_addr;
 

	strcpy(g_lua_fun_name, lua_notify_fun_name);
	funchook_t *ft = funchook_create(); 
	strcpy(g_sig, sig);
	funchook_prepare_jit(ft, (void**)&origion_hook_fun_addr);
	funchook_install(ft, 0);
	return 0;
}


int get_current_stack(lua_State* L)
{
	void* cur_stack[STACK_LIMIT] = {0};

	char* str = malloc(STACK_LIMIT * 256);
	int j = 0;

	int stack_size = backtrace(cur_stack, STACK_LIMIT);

	int cur_pos = 0;

	for(j=0; j< stack_size; j++)
	{
		Dl_info info;
		void* fun_addr = cur_stack[j];
		dladdr(fun_addr, &info);		
		int xx = (int)((unsigned long long )fun_addr - (unsigned long long )info.dli_fbase);
		cur_pos += sprintf(str + cur_pos, "## %s %d %p %p\n", info.dli_fname, xx,  fun_addr, info.dli_fbase);
	} 

	lua_pushstring(L,str);

	free(str);

	return 1;
}


int get_fun_addr(lua_State* L)
{
	const char* funname = lua_tostring(L, -1);

	void* addr = dlsym(RTLD_NEXT, funname);

	lua_pushnumber(L,(long)addr);

	return 1;
}


int try_hook_thread(void* data){

	lua_State *L =	luaL_newstate();

	luaL_openlibs(L);	

	lua_register(L, "set_hook", set_hook);

	lua_register(L, "get_so_load_base", get_so_load_base);
		
	luaL_dofile(L, "hook.lua");
}

pid_t fork(){
	printf("skip fork, just return 0...\n");
	return 0;
}

/************************** 
luajit的lj_alloc_f函数由于其特殊性，无法被HOOK(需要更新HOOK库，由于该情形较少发生，所以暂时不更新HOOK库，简单规避)
*******************************/
typedef void * (*lj_alloc_f_hook_type)(void *msp, void *ptr, size_t osize, size_t nsize);
static lj_alloc_f_hook_type s_mem_hook_addr = NULL;
void *lj_alloc_f_hook(void *msp, void *ptr, size_t osize, size_t nsize){
	if(t_L == NULL){
		
		t_L =  luaL_newstate();

		printf("t_L=%p\n", t_L);
			
		luaL_openlibs(t_L);	

		lua_register(t_L,"get_current_stack", get_current_stack);
		lua_register(t_L, "get_so_load_base", get_so_load_base);

		luaL_loadfile(t_L, "hook.lua") ;
		lua_pcall(t_L, 0, LUA_MULTRET, 0);
	}	
	lua_getglobal(t_L, "lj_alloc_f");

	lua_pushnumber(t_L, (double)(long)msp);
	lua_pushnumber(t_L, (double)(long)ptr);
	lua_pushnumber(t_L, (double)osize);
	lua_pushnumber(t_L, (double)nsize);

	lua_pcall(t_L, 4, 0, 0);
	
	return  s_mem_hook_addr(msp, ptr, osize, nsize);

}

typedef void* (*lj_state_newstate_hook_type)(void* a, void* b);
lj_state_newstate_hook_type s_newstate_fun = NULL;
void* lj_state_newstate_hook(void* a, void* b)
{
	s_mem_hook_addr = (lj_alloc_f_hook_type)a;
	return 	s_newstate_fun(lj_alloc_f_hook, b);
}


int hook_luajit_mem(lua_State* L){

	long new_fun_ptr = (long)(lua_tonumber(L, -1));
	
	s_newstate_fun = (void*)new_fun_ptr;

	funchook_t *fork_ft = funchook_create();
	funchook_prepare(fork_ft, (void**)&s_newstate_fun, lj_state_newstate_hook);
	funchook_install(fork_ft, 0);

	return 0;

}


typedef void* (*luaL_newstate_funtype)();
static luaL_newstate_funtype s_luaL_newstate_fun = NULL;
static void* s_luaprofile_handle = NULL;
void* hook_luaL_newstate_fun(){

	if(NULL != s_process_luaState){
		printf("s_process_luaState is not null cant support NOW");
		return NULL;
	}
	
	s_process_luaState = s_luaL_newstate_fun();

	typedef void(*fun_init_profiler)(lua_State *L);
	 

	s_luaprofile_handle = dlopen("cpuprofiler.so", 1);
	 
	fun_init_profiler init_fun = (fun_init_profiler)dlsym(s_luaprofile_handle, "init_profiler");
	 
	init_fun(s_process_luaState);

	char fileName[256];
	
	sprintf(fileName, "profiler_start('/data/luaprofiler.data.txt.%d', 1)", (int)getpid());
	
	luaL_dostring(s_process_luaState, fileName);

	return s_process_luaState;
}




int start_luaprofiler(lua_State* L)
{
	s_luaL_newstate_fun  =  (void*)(long)lua_tonumber(L, -1);

	funchook_t *fork_ft = funchook_create();

	
	funchook_prepare(fork_ft, (void**)&s_luaL_newstate_fun, hook_luaL_newstate_fun);
	
	funchook_install(fork_ft, 0);

	return 0;
}


void __attribute__((constructor)) Init()
{
	pthread_t id_1;

	funchook_t *fork_ft = funchook_create();
	log_init();


	funchook_set_debug_file("funchook.log");
	void  (*RealFork)(void);
	RealFork = dlsym(RTLD_NEXT, "fork");

	funchook_prepare(fork_ft, (void**)&RealFork, fork);
	funchook_install(fork_ft, 0);	


	lua_State *L =  luaL_newstate();
	
	luaL_openlibs(L);	
	lua_register(L, "get_so_load_base", get_so_load_base);
	lua_register(L, "set_hook", set_hook);
	lua_register(L, "get_fun_addr", get_fun_addr);
	lua_register(L, "hook_luajit_mem", hook_luajit_mem);
	lua_register(L, "start_luaprofiler", start_luaprofiler);
	luaL_dofile(L, "hook.lua");
	
	/*
	int ret=pthread_create(&id_1,NULL,(void  *) try_hook_thread,NULL);
	if(ret != 0){
		 
		exit(0);
	}*/

	 	
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



