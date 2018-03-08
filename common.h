#ifndef __COMMON_H

#define __COMMON_H
#ifdef __cplusplus
extern "C" {
#endif
#include <sys/types.h>
unsigned long long current_usecond();
__attribute((visibility("default"))) double current_tick();
 __attribute((visibility("default"))) long ffi_get_tid();
void log_init(const char*);
__attribute((visibility("default")))  void ffi_log_out(char* str);
unsigned long long current_msecond();
__attribute((visibility("default")))  char* ffi_get_sock_info(int fd);
__attribute((visibility("default")))  char* ffi_get_peer_info(int fd);

__attribute((visibility("default"))) long  ffi_get_so_load_base(const char* so_path);


#define MAX_STACK_LIMIT (20)

typedef struct _StackInfoNode{

	int m_add_cnt;

	int m_del_cnt;
	int m_alloc_size;

	int m_free_size;
	void* m_stack_data[MAX_STACK_LIMIT];

	int m_stack_size;

	struct _StackInfoNode* m_next;

	unsigned long m_hash;

	int   m_flag; // 0 for C addr backtrace, 1 for lua Source line..
	
}StackInfoNode;

typedef struct _StackInfoArray{

	int m_size;

	int m_stackLimit;

	StackInfoNode** m_array;
	
}StackInfoArray;



void InitStackModule();
StackInfoArray* NewStackInfoArray(int size, int stackLimit);
StackInfoNode* CurrentStackInfoNode(StackInfoArray* m, const char* luainfo);
void DumpStackInfoArray(StackInfoArray* m, const char* fileName);

typedef char* (*ctl_thread_handle_fun)(char* cmd);

void init_ctl_thread(const char* sockpath,ctl_thread_handle_fun handlefun);



#ifdef __cplusplus
}
#endif

#endif