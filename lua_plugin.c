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

void add_lua_interface(lua_State* L){

	lua_register(L, "get_sock_info", get_sock_info);
	lua_register(L, "get_peer_info", get_peer_info);	
	lua_register(L, "is_sock_nonblock", is_sock_nonblock);		
}





