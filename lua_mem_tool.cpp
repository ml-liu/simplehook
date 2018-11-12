#include <sys/types.h>
#include <sys/socket.h>

#include <unistd.h>
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>

#include <sys/un.h>


#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#if defined(linux)
#define __USE_GNU 1
#include <dlfcn.h>
#endif

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
#include <vector>


extern "C" {
#include <sys/epoll.h>
#include "arpa/inet.h"
#include "funchook.h"
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include "queue.h"

}


#define MAX_DUMP_COUNT (1024)

__thread int* t_can_dump = NULL;

int* get_can_dump_array(){
	if(t_can_dump == NULL){
		t_can_dump = new int[MAX_DUMP_COUNT];
		memset(t_can_dump, 0, sizeof(int) * MAX_DUMP_COUNT);
	}

	return t_can_dump;
}


#define MEMORY_PROFILER 1
#define CPU_PROFILER    2
#define SIMPLE_MEMORY_STAT 4

int g_working_mode = 0;

int g_cpuStatIndex = 0;
int g_need_cpuStateIndex = 0;
int g_nowStatIndex = 0;


struct LuaStateCpuData{
	LuaStateCpuData():m_level(0){};
	int m_level;
};

class LuaStateMap
{
public:
	LuaStateMap()
	{
	}

	void add_state(void* L)
	{
		m_map[L] = new LuaStateCpuData;		
	}

	
	LuaStateCpuData* get_state_data(void* L){
		std::map<void *, LuaStateCpuData*>::iterator it = m_map.find(L);

		LuaStateCpuData* ret = NULL;

		if(it != m_map.end()){
			ret = it->second;
		}else{
			ret = new LuaStateCpuData;
			m_map[L] = ret ;
		}
		
		return ret;
	}

private:
	pthread_mutex_t m_mutex;
	std::map<void *, LuaStateCpuData*> m_map;
	
};

__thread LuaStateMap* t_luaStateMap = NULL;

LuaStateMap* get_thread_luastate_map(){
	if(t_luaStateMap == NULL)
		t_luaStateMap = new LuaStateMap;

	return t_luaStateMap;
}




#define MYASSERT(a) do{\
	if(!(a)){\
		printf("%s ERROR!!!!\n", #a);\
		exit(0);\
		}\
		}while(0);





 
 __thread std::vector<std::string>* t_require_vec = NULL;
 
 std::vector<std::string>& get_require_vec()
 {
 	if(t_require_vec == NULL){
 		printf("new vector");
 		t_require_vec = new std::vector<std::string>;
 	}
 
 	return *t_require_vec;
 }



__thread std::vector<std::string>* t_seacher_Lua_vec = NULL;

std::vector<std::string>& get_seacher_Lua_vec()
{
	if(t_seacher_Lua_vec == NULL){
		printf("new vector");
		t_seacher_Lua_vec = new std::vector<std::string>;
	}

	return *t_seacher_Lua_vec;
}




struct LuaStateMemState{
	LuaStateMemState(){
		m_mem = 0;
		m_state_ptr = NULL;
		m_tid = 0;
	}
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


/************************** 
luajit的lj_alloc_f函数由于其特殊性，无法被HOOK(需要更新HOOK库，由于该情形较少发生，所以暂时不更新HOOK库，简单规�?
*******************************/

typedef void * (*lj_alloc_f_hook_type)(void *msp, void *ptr, size_t osize, size_t nsize);

static lj_alloc_f_hook_type s_mem_hook_addr = NULL;

__thread std::map<void*, int>* g_ptr_map;

typedef int (*ll_require_type) (lua_State *L);
typedef const char * (*luaL_checklstring_type) (lua_State *L, int arg, size_t *len);

typedef int (*searcher_Lua_type) (lua_State *L);
typedef int (*lua_getstack_type)(lua_State *L, int level, lua_Debug *ar);
typedef int (*lua_getinfo_type)(lua_State *L, const char *what, lua_Debug *ar);
typedef int  (*lua_sethook_type)(void*, void*, int mask, int count);
typedef void* (*lua_tocfunction_type) (void *L, int idx);
lua_tocfunction_type s_lua_tocfunction = NULL;

typedef int (*luaD_rawrunprotected_type) (lua_State *L, void* f, void *ud) ;

typedef void  (*lua_settop_type)(void *L, int idx);
lua_settop_type s_lua_settop = NULL;

luaD_rawrunprotected_type s_luaD_rawrunprotected = NULL;


lua_getstack_type s_lua_getstack = NULL;
lua_getinfo_type  s_lua_getinfo = NULL;
lua_sethook_type s_lua_sethook = NULL;


ll_require_type s_ll_require = NULL;
ll_require_type s_old_ll_require = NULL;


searcher_Lua_type s_searcher_Lua = NULL;
searcher_Lua_type s_old_searcher_Lua = NULL;





luaL_checklstring_type s_luaL_checklstring = NULL;



__thread char* t_luainfo = NULL;

unsigned long long g_total_alloc_lua_mem = 0;

unsigned long long g_total_free_lua_mem = 0;

#define MAX_STACK_LENGTH 32


static void callhook(lua_State *L, lua_Debug *ar){

	

	LuaStateCpuData* data = get_thread_luastate_map()->get_state_data(L);

	// Э���ݲ�֧��
	if(NULL == data)
		return;

	if(ar->event != 0 && ar->event != 1)
		return;

	int stack_level = 0;

	if(ar->event == 0)
	{
		stack_level = data->m_level;
		data->m_level++;
	}
	else
	{ 
		data->m_level--;
		stack_level = data->m_level;
	}

	

	if(!get_can_dump_array()[g_nowStatIndex]){
		return;
	}


	int tid  = syscall(SYS_gettid);
	

	char* buffer = (char*)malloc(256);
	buffer[0] = 0;	
	s_lua_getinfo(L, "flnS", ar);

	unsigned long long tick = program_tick();
	if( ar->source &&  strcmp(ar->source, "=[C]") == 0)
	{ 
		void* cfun = s_lua_tocfunction(L, -1);
		snprintf(buffer, 255, "\n[L=%p][%d][%d][%d][l=%d][%llu]CFUN %p",L, g_cpuStatIndex, tid,ar->event, stack_level, tick , cfun);
	}else{
		snprintf(buffer , 255, "\n[L=%p][%d][%d][%d][l=%d][%llu]%s(%d) %s",L, g_cpuStatIndex, tid,ar->event, stack_level, tick, ar->source, ar->linedefined, ar->name);
	}

	

	buffer[255] = 0;

	s_lua_settop(L, -2);

	ffi_log_out(buffer);
	

}
char* g_copy_string(const char* str) {
     
    if (str) {
        char* tmp = (char*)malloc(strlen(str) + 1);
        strcpy(tmp, str);
        return tmp;
    }
    return 0;
}

class CFunctionCache
{
public:
	CFunctionCache(){

		pthread_mutex_init(&m_mutex, NULL);
	}

	char* get_fun_ptr(void* p)
	{

		char* ret = NULL;
		pthread_mutex_lock(&m_mutex);
		
		std::map<void*,char*>::iterator it = m_lua_fun_cache.find(p);

		if(it == m_lua_fun_cache.end()){
			ret = NULL;
		}else{
			ret = it->second;
		}


		pthread_mutex_unlock(&m_mutex);

		return ret;
	}

	void add_fun(void* p, const char* pname ){
		pthread_mutex_lock(&m_mutex);
		std::map<void*,char*>::iterator it = m_lua_fun_cache.find(p);
		if(it == m_lua_fun_cache.end()){
			m_lua_fun_cache[p] = g_copy_string(pname);
		}
		pthread_mutex_unlock(&m_mutex);
	}


private:
	std::map<void*,char*> m_lua_fun_cache;

	pthread_mutex_t m_mutex;	
};


CFunctionCache* g_cfun_cache  = NULL;


class LuaFunctionCache
{
public:
	LuaFunctionCache(){

		pthread_mutex_init(&m_mutex, NULL);
	}

	char* get_fun_ptr(const char* fname)
	{

		char* ret = NULL;
		pthread_mutex_lock(&m_mutex);
		
		std::map<std::string,char*>::iterator it = m_lua_fun_cache.find(fname);

		if(it == m_lua_fun_cache.end()){

			ret = g_copy_string(fname);
			m_lua_fun_cache[fname] =ret;
			
		}else{
			ret = it->second;
		}


		pthread_mutex_unlock(&m_mutex);

		return ret;
	}


private:
	std::map<std::string,char*> m_lua_fun_cache;

	pthread_mutex_t m_mutex;	
};


LuaFunctionCache* g_lua_fun_cache = NULL;


class StackData{
public:	
	StackData()
	{			
		memset(m_ptr_array, 0, sizeof(m_ptr_array));
		m_cur_index= 0;
		m_lua_stack_cnt = 0;
	}

	bool operator<(const StackData& a)const
	{

		if(this->m_cur_index < a.m_cur_index){
			return true;
		}


		if(this->m_cur_index > a.m_cur_index){
			return false;
		}

		for(int i = 0; i < a.m_cur_index; i++){

			if( (unsigned long long)this->m_ptr_array[i] <  (unsigned long long)a.m_ptr_array[i]){
				return true;
			}
		}

		return false;
		
	}

	void add_lua_fun(const char* fname)
	{
		if(m_cur_index >= MAX_STACK_LENGTH)
			return;	
		m_ptr_array[m_cur_index] = g_lua_fun_cache->get_fun_ptr( fname);

		m_lua_stack_cnt++;
		m_cur_index++;
	}

	void dump_stack_file(FILE* fp){	
        fprintf(fp,"%p [LUASTACK]=", this);
		int i = 0;
		for(i = 0; i < m_lua_stack_cnt; i++){
			if(i == 0)
			{
				fprintf(fp,"%s", (char*)m_ptr_array[i]);
			}
			else{
				fprintf(fp,"|%s", (char*)m_ptr_array[i]);
			}
		}

		fprintf(fp,"\r\n"); 		
	}

	void add_mono_fun(void* func)
	{
		if(m_cur_index >= MAX_STACK_LENGTH){
			printf("add_mono_fun too much....");
			return;
		}

		m_ptr_array[m_cur_index] = func;
		m_cur_index++;
	}

	void add_dofile_fun(void* func){

	}
protected:
	void* m_ptr_array[MAX_STACK_LENGTH];
	
	int   m_cur_index;

	int   m_lua_stack_cnt;

	 
};

class StackStatData
{
public:
	StackStatData():m_alloc_size(0),m_alloc_cnt(0),m_free_cnt(0),m_free_size(0), m_next(NULL){};
	long long m_alloc_size;
	long long m_free_size;
	long long m_alloc_cnt;
	long long m_free_cnt; 
	StackData m_stackData;
	StackStatData* m_next;
};





#define MAX_LUA_STACK_CNT (5000000)
class StackMap
{

public:
	StackMap(){
		m_stack_cnt = 0;
		pthread_mutex_init(&m_mutex, NULL);
		m_stack_list_head = NULL;
	}

	StackStatData* get_stack_data(const StackData& p){

		StackStatData* ret = NULL;

		bool need_dump = false;
		
		pthread_mutex_lock(&m_mutex);

		std::map<StackData,StackStatData*>::iterator it = m_stack_cache.find(p);

		if(it == m_stack_cache.end()){
			ret = new StackStatData;
			ret->m_stackData  = p;
			m_stack_cache[p] = ret;
			need_dump = true;



			ret->m_next = m_stack_list_head;
			m_stack_list_head = ret;

			m_stack_cnt++;			
		}else{
			//printf("found in cache*****\n");
			ret = it->second;
		}
		
		pthread_mutex_unlock(&m_mutex);

		//if(need_dump){
			//ret->dump_stack_file();
		//}

		return ret;
	}

public:
	std::map<StackData,StackStatData*> m_stack_cache;
	pthread_mutex_t m_mutex;	

	StackStatData* m_stack_list_head;

	unsigned long long m_stack_cnt ;

};

StackMap* g_stack_map = NULL;




class PtrInfoMap{
public:
	PtrInfoMap(){
		pthread_mutex_init(&m_mutex, NULL);
	}

	void add_ptr(void* prt, StackStatData* sm){
		pthread_mutex_lock(&m_mutex);
		m_map[prt] = sm;
		pthread_mutex_unlock(&m_mutex);		
	}

	StackStatData* remove_ptr(void* ptr){
		StackStatData* ret = NULL;
		pthread_mutex_lock(&m_mutex);
		std::map<void*, 	StackStatData*>::iterator it = m_map.find(ptr);
		if(it != m_map.end()){
			ret = it->second;
			m_map.erase(ptr);
		}		
		pthread_mutex_unlock(&m_mutex);	
		return ret;
	}

	void* get_ptr(void* ptr)
	{
		StackStatData* ret = NULL;
		pthread_mutex_lock(&m_mutex);
		std::map<void*, 	StackStatData*>::iterator it = m_map.find(ptr);
		if(it != m_map.end()){
			ret = it->second;
		}		
		pthread_mutex_unlock(&m_mutex);	
		return ret;
	}

private:	
	pthread_mutex_t m_mutex;

	std::map<void*, 	StackStatData*> m_map;
};



PtrInfoMap* g_ptrinfo_map = NULL;


__thread char* t_luaStack = NULL;
__thread char* t_tmpbuff = NULL;
static const char* get_base_name(const char* fullpath){

	if (NULL == fullpath)
		return "";
	
	int len = strlen(fullpath);

	if(len == 0)
		return fullpath;

	int i = 0;
	
	for(i = len - 1; i > 0; i--){

		if(fullpath[i] == '/'){
			if(i < len - 1){
				return fullpath + i + 1;
			}
		}
	}

	return fullpath;
	
}

StackStatData* dumpstack(void* luaState, lua_Debug *var){

	int ev = var->event;

	if(t_luaStack == NULL){
		t_luaStack = (char*)malloc(25000);
	}

	if(t_tmpbuff == NULL)
		t_tmpbuff = (char*)malloc(25000);
	
	int level = 0;
	int pos = 0;
	

	
	lua_Debug ar;
	t_luaStack[0] = 0;

	StackData m_stack_data;

	int require_idx = 0;
	int searchLua_idx = 0;

	
	while(luaState != NULL && s_lua_getstack((lua_State*)luaState, level, &ar) == 1)
		{
				t_luaStack[0] = 0;	
				s_lua_getinfo((lua_State*)luaState, "flnS", &ar);

				if(ar.source != NULL)
				     snprintf(t_tmpbuff,100, "%s" ,ar.source);
				else
				 	t_tmpbuff[0] = 0;


				
				

				if( ar.source &&  strcmp(ar.source, "=[C]") == 0)
				{ 
			     	void* cfun = s_lua_tocfunction(luaState, -1);

					if(cfun == s_old_ll_require){
						MYASSERT(require_idx < get_require_vec().size());
						snprintf(t_luaStack , 98, "ll_require(%s)", get_require_vec()[get_require_vec().size() - 1 - require_idx].c_str());
						require_idx++;
					}else if(cfun == s_old_searcher_Lua){
						MYASSERT(searchLua_idx < get_seacher_Lua_vec().size());
						snprintf(t_luaStack , 98, "searcher_Lua(%s)", get_seacher_Lua_vec()[get_seacher_Lua_vec().size() - 1 - searchLua_idx].c_str());
						searchLua_idx ++;
					}
					else{
						snprintf(t_luaStack, 98, "CFUN %p",  cfun);
					}
				}else{
					snprintf(t_luaStack , 127, "%s(%d):%s", t_tmpbuff,(int)ar.linedefined,  ar.name);
				}
				s_lua_settop(luaState, -2);
			

				//printf("%s", t_luaStack);

				m_stack_data.add_lua_fun(t_luaStack);
					
				level ++;
		}
	
	StackStatData* stackPtr = g_stack_map->get_stack_data(m_stack_data);

	MYASSERT(require_idx == get_require_vec().size());
	MYASSERT(searchLua_idx == get_seacher_Lua_vec().size());

	

	return stackPtr;

}






void *lj_alloc_f_hook(void *msp, void *ptr, size_t osize, size_t nsize){

	void* newPtr = NULL;

	int state_idx = (int)(long long)msp;


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


	if(ptr != NULL && (g_working_mode & MEMORY_PROFILER) ){
		StackStatData* s = g_ptrinfo_map->remove_ptr(ptr);
		if(NULL != s){
			s->m_free_cnt++;
			s->m_free_size += osize;
			
			
		}else{
			printf("error 2 ptr=%p ud=%p osize=%d, nsize=%d", ptr,msp ,(int)osize, (int)nsize);
		}
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


	LuaStateMemState& d = g_lua_state_arr[state_idx];
	
	if((g_working_mode & MEMORY_PROFILER) && newPtr != NULL && d.m_state_ptr != NULL)
	{
		
		lua_Debug var;
		var.event = 0;
		
		StackStatData* s = dumpstack(d.m_state_ptr, &var);
		g_ptrinfo_map->add_ptr(newPtr, s);
		s->m_alloc_cnt++;
		s->m_alloc_size += nsize;
	}

	

	return newPtr;

}





typedef void* (*lj_state_newstate_hook_type)(void* a, void* b);

lj_state_newstate_hook_type s_newstate_fun = NULL;

void* lj_state_newstate_hook(void* a, void* b)
{

	s_mem_hook_addr = (lj_alloc_f_hook_type)a;





	void* ret = NULL;
	if( (g_working_mode & MEMORY_PROFILER) || (g_working_mode & SIMPLE_MEMORY_STAT) ){
		int cur_idx = __sync_fetch_and_add(&g_lua_lua_state_idx, 1);
		if(cur_idx >= MAX_LUA_STATE_COUNT){
			exit(-1);
		}		
	    ret = 	s_newstate_fun((void*)lj_alloc_f_hook, (void*)cur_idx);
		g_lua_state_arr[cur_idx].m_state_ptr = ret;
	}else{
		ret = s_newstate_fun(a, b );
	}



	if(g_working_mode & CPU_PROFILER){
		s_lua_sethook(ret, (lua_Hook)callhook,19, 0);
	}

	return ret;
	
}


__thread int xxx = 0;

class AutoClear
{public:
	AutoClear(std::vector<std::string>& vec,  const char* s):m_vec(vec){
		m_vec.push_back(s);
	}
	~AutoClear(){
		m_vec.pop_back();	
	}

	char* m_s;	

	std::vector<std::string>& m_vec;
};

static int _new_ll_require (lua_State *L)
{
	

	const char* s = s_luaL_checklstring(L, -1, NULL);
	AutoClear s1(get_require_vec(), s);

	//printf("_new_ll_require %s %d\n", s, (int) get_require_vec().size());
	//printf("thread id xxx=%d :%d _new_ll_require %s get_require_vec() size:%d\n",xxx, (int)pthread_self(), s, (int)get_require_vec().size());	

	//get_require_vec().push_back(s);

	int ret =  s_ll_require(L);
	
	//printf("end thread id :%d _new_ll_require %s get_require_vec() size:%d\n", (int)pthread_self(), s, (int)get_require_vec().size());	

	return ret;
}


int _new_searcher_Lua (lua_State *L)
{
	const char* s = s_luaL_checklstring(L, -1, NULL);

	AutoClear s1(get_seacher_Lua_vec(), s); 
	//printf("_new_searcher_Lua %s %d\n", s, (int) get_seacher_Lua_vec().size());

	int ret = s_searcher_Lua(L);

	return ret;
}



struct RawRunPotectData
{
	RawRunPotectData(int level = 0){
		m_require_size = get_require_vec().size();
		m_searchLua_size = get_seacher_Lua_vec().size();
		m_level = level;
		
	}
	int m_require_size;
	int m_searchLua_size;
	int m_level;
};

__thread std::vector<RawRunPotectData>* t_pvec = NULL;

std::vector<RawRunPotectData>& get_pcall_vec(){
	if(NULL == t_pvec)
		t_pvec = new std::vector<RawRunPotectData>;

	return *t_pvec;
}

__thread int t_lua_pcallk_depth = 0;

typedef int (*type_lua_pcallk) (void *L, int nargs, int nresults, int errfunc,void* ctx, void* k);

type_lua_pcallk real_lua_pcallk = NULL;

int new_lua_pcallk (void *L, int nargs, int nresults, int errfunc,void* ctx, void* k)
{
	
	unsigned long long s = current_usecond();

	int depth = t_lua_pcallk_depth;

	if(depth != get_pcall_vec().size()){
		printf("depth=%d, vecsize=%d\n", depth, (int)get_pcall_vec().size());
	}
	if(depth == 0){
		int x = get_can_dump_array()[g_nowStatIndex];
		get_can_dump_array()[g_nowStatIndex] = (g_cpuStatIndex == g_need_cpuStateIndex ? 0 : 1);
		if(x != get_can_dump_array()[g_nowStatIndex])
			ffi_flush_log();
	}

	t_lua_pcallk_depth++;
	int ret =  real_lua_pcallk(L, nargs, nresults, errfunc, ctx, k);
	t_lua_pcallk_depth--;
	return ret;
}


int _new_luaD_rawrunprotected (lua_State *L, void* f, void *ud){


	LuaStateCpuData* cpuData = get_thread_luastate_map()->get_state_data(L);


	get_pcall_vec().push_back(RawRunPotectData((cpuData!=NULL ? cpuData->m_level:0)));


	static int s_lastdumpIdx = 0;
	
	int ret = s_luaD_rawrunprotected(L, f, ud);

	 



	RawRunPotectData data = get_pcall_vec()[get_pcall_vec().size() - 1];

	get_pcall_vec().pop_back();

	if(data.m_require_size != get_require_vec().size()){
		
		MYASSERT(get_require_vec().size() == data.m_require_size + 1)
		printf("ERROR!!!! require newsize=%d nowsize=%d ERROR str:%s\n", data.m_require_size, (int)get_require_vec().size(), get_require_vec()[get_require_vec().size() - 1].c_str());
		get_require_vec().resize(data.m_require_size, "");
	}


	if(data.m_searchLua_size != get_seacher_Lua_vec().size())
	{
		printf("data.m_searchLua_size=%d, get_seacher_Lua_vec().size=%d\n", data.m_searchLua_size, (int)get_seacher_Lua_vec().size());
		MYASSERT(data.m_searchLua_size < get_seacher_Lua_vec().size());
		printf("search lua %d %d\n", data.m_searchLua_size, get_seacher_Lua_vec().size());
		get_seacher_Lua_vec().resize(data.m_searchLua_size);
	}

	if(cpuData != NULL&& data.m_level != cpuData->m_level){
		printf("ERROR HAPPENs...\n");
		cpuData->m_level = data.m_level;
	}
	

	return ret;
}






int hook_lua_mem(lua_State* L){

	long new_fun_ptr  = (long)(lua_tonumber(L, -4));
	long getstack_ptr = (long)(lua_tonumber(L, -3));
	long getinfo_ptr  = (long)(lua_tonumber(L, -2));
	long sethook_ptr  = (long)(lua_tonumber(L, -1));	

	
	s_newstate_fun = (lj_state_newstate_hook_type)(void*)new_fun_ptr;
	s_lua_getstack = (lua_getstack_type)getstack_ptr;
	s_lua_getinfo = (lua_getinfo_type)getinfo_ptr;
	s_lua_sethook = (lua_sethook_type)sethook_ptr;

	s_lua_tocfunction = (lua_tocfunction_type)(long)(lua_tonumber(L, -5));
	s_lua_settop = (lua_settop_type)(long)(lua_tonumber(L, -6));

	s_ll_require = (ll_require_type)(long)(lua_tonumber(L, -7));
	s_old_ll_require = s_ll_require;
	s_luaL_checklstring = (luaL_checklstring_type)(long)(lua_tonumber(L, -8));	

	s_luaD_rawrunprotected =  (luaD_rawrunprotected_type)(long)(lua_tonumber(L, -9));	

	s_searcher_Lua = (searcher_Lua_type)(long)(lua_tonumber(L, -10));	

	g_working_mode = (int)(lua_tonumber(L, -11));

	s_old_searcher_Lua = s_searcher_Lua;

	real_lua_pcallk = (type_lua_pcallk)(long)(lua_tonumber(L, -12));

	printf("g_working_mode=%d (memory:0  cpu:1)\n", g_working_mode);
	

	funchook_t *fork_ft = funchook_create();
	funchook_prepare(fork_ft, (void**)&s_newstate_fun, (void*)lj_state_newstate_hook);
	funchook_install(fork_ft, 0);

	if(g_working_mode & MEMORY_PROFILER){
		funchook_t *lr = funchook_create();
		funchook_prepare(lr, (void**)&s_ll_require, (void*)_new_ll_require);
		funchook_install(lr, 0);	

		funchook_t *lr2 = funchook_create();
		funchook_prepare(lr2, (void**)&s_searcher_Lua, (void*)_new_searcher_Lua);
		funchook_install(lr2, 0);
	}


	
	

	
	funchook_t *lr1 = funchook_create();
	funchook_prepare(lr1, (void**)&s_luaD_rawrunprotected, (void*)_new_luaD_rawrunprotected);
	funchook_install(lr1, 0);	

	
	funchook_t *lr3 = funchook_create();
	funchook_prepare(lr3, (void**)&real_lua_pcallk, (void*)new_lua_pcallk);
	funchook_install(lr3, 0);	

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
		printf("begin flush now!!!");
		printf("begin dump now!!!");
		
		char filename[100];
		sprintf(filename, "/tmp/stack.%d.%d.txt", getpid(),s_need_dump_idx);
		
		FILE* fpstack = fopen(filename, "w");
		
		sprintf(filename, "/tmp/lualog.%d.%d.txt", getpid(),s_need_dump_idx);
		
		FILE* fplog = fopen(filename, "w");
		printf("fpstack:%p, fplog:%p", fpstack, fplog);
		
		
		 
		 
	
		
		printf("cnt=%lld", g_stack_map->m_stack_cnt);		
		StackStatData* item =g_stack_map->m_stack_list_head;
		while(item != NULL){
			
			long long unfreesize = item->m_alloc_size - item->m_free_size;
			
			if(unfreesize > 0)
			{
				item->m_stackData.dump_stack_file(fpstack);
		
				fprintf(fplog, "size=%lld StackPtr=%p malloc=%lld freecnt=%lld mallocsize=%lld freesize=%lld\r\n", unfreesize, &item->m_stackData, item->m_alloc_cnt, item->m_free_cnt, item->m_alloc_size, item->m_free_size); 	
			}

			item = item->m_next;
		}
		
		
		fclose(fplog);
		fclose(fpstack);

	}else if(strncmp(cmd, "startcpu", 8) == 0){
		g_need_cpuStateIndex++;
		sprintf(res, "g_need_cpuStateIndex=%d", g_need_cpuStateIndex);
		g_nowStatIndex = g_cpuStatIndex;

		char* tmplog = (char*)malloc(200);
		sprintf(tmplog, "start nowidx %d tick %llu\n", g_nowStatIndex, program_tick());
		ffi_log_out(tmplog);
		
	}else if(strncmp(cmd, "stopcpu", 7) == 0){
		g_cpuStatIndex = g_need_cpuStateIndex;
		sprintf(res, "g_cpuStatIndex=%d", g_cpuStatIndex);
		char* tmplog = (char*)malloc(200);
		sprintf(tmplog, "stop nowidx %d tick %llu\n", g_nowStatIndex, program_tick());
		ffi_log_out(tmplog);

		
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


	g_ptrinfo_map = new PtrInfoMap;
    g_lua_fun_cache = new LuaFunctionCache;
	g_stack_map = new StackMap;
	g_cfun_cache = new CFunctionCache;

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
	lua_register(L, "hook_lua_mem", hook_lua_mem);
	luaL_dofile(L, "hook.lua");

	init_ctl_thread("/tmp/luameme.sock", ctl_thread_handle);
	
	/*
	int ret=pthread_create(&id_1,NULL,(void  *) try_hook_thread,NULL);
	if(ret != 0){
		 
		exit(0);
	}*/

	 	
}



