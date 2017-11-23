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
#include "netinet/in.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>



__thread char* t_get_sock_info_ThreadBuf = NULL;
__thread char* t_get_peer_info_ThreadBuf = NULL;


int get_sock_info(lua_State* L){

	int fd = lua_tointeger(L, -1);

	struct sockaddr_in serv, guest;  
	char serv_ip[20] = {0};  

	socklen_t serv_len = sizeof(serv);	
	 
	getsockname(fd, (struct sockaddr *)&serv, &serv_len);  
	inet_ntop(AF_INET, &serv.sin_addr, serv_ip, sizeof(serv_ip));   
	printf("host %s:%d \n", serv_ip, ntohs(serv.sin_port));  
	lua_pushstring(L, serv_ip);
	lua_pushinteger(L,ntohs(serv.sin_port));
	return 2;
	
}

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


int get_peer_info(lua_State* L){
	int fd = lua_tointeger(L, -1);

	struct sockaddr_in serv, guest;  
	char serv_ip[20] = {0};  

	socklen_t serv_len = sizeof(serv);	
	 
	getpeername(fd, (struct sockaddr *)&serv, &serv_len);  
	inet_ntop(AF_INET, &serv.sin_addr, serv_ip, sizeof(serv_ip));   
	printf("host %s:%d \n", serv_ip, ntohs(serv.sin_port));  
	lua_pushstring(L, serv_ip);
	lua_pushinteger(L,ntohs(serv.sin_port));


	return 2;
}

int is_sock_nonblock(lua_State* L){
	
	int fd = lua_tointeger(L, -1);	
	int  flags = fcntl(fd, F_GETFL, 0);

	printf("sockblock:%d\n", flags);

	lua_pushinteger(L, (flags & O_NONBLOCK) ? 1 : 0);

	return 1;
}

int get_epoll_event_type(lua_State* L){
	
	 struct epoll_event* p = (struct epoll_event*)(void*)(long)lua_tonumber(L, -1);

	 lua_pushnumber(L,(double)p->events);

	 return 1;
}


void add_lua_interface(lua_State* L){

	lua_register(L, "get_sock_info", get_sock_info);
	lua_register(L, "get_peer_info", get_peer_info);	
	lua_register(L, "is_sock_nonblock", is_sock_nonblock);	
	lua_register(L, "get_epoll_event_type", get_epoll_event_type);
}







