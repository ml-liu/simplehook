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
}





class ConnectInfo{
public:
	ConnectInfo():send_bytes(0),recv_bytes(0),last_errcode(0),close_reason(0),create_ts(0),recv_error_cnt(0),send_error_cnt(0),send_cnt(0),recv_cnt(0),
		last_recv_ret(0),last_send_ret(0), has_sock_info(0){

		create_ts = current_tick();
	};


public:	
	int send_bytes;
	int recv_bytes;
	int last_errcode;
	int close_reason;
	double create_ts;
	int recv_error_cnt;
	int send_error_cnt;
	int send_cnt;
	int recv_cnt;
	int last_recv_ret;
	int last_send_ret;
	int has_sock_info;
	double last_send_ts;
	double last_recv_ts;
	std::string sock_info;
};


static std::map<int, ConnectInfo> g_net_stat_map;

static pthread_mutex_t g_mutex;

void __attribute__((constructor)) Init(){
	pthread_mutex_init(&g_mutex, NULL);

	char* b = (char*)malloc(20);

	sprintf(b, "net plugin init");

	ffi_log_out(b);
}


 extern "C"  __attribute((visibility("default"))) void add_stat(int fd,int ev, int op, long value, int err){

	char* out_buff = NULL;

	if(ev == 0 || ev == 3 || ev == 4){
		out_buff = (char*)malloc(1024);
	}
	
	pthread_mutex_lock(&g_mutex);

	ConnectInfo& info = g_net_stat_map[fd];

	// 0 socketcreate  1 send 2 recv 3 close 4 accept

	if(ev == 1){
		if(value > 0){
			info.send_bytes += value;
		}

		info.last_send_ret = value;
		info.last_send_ts = current_tick();
	}else if(ev == 2){
		if(value > 0){
			info.recv_bytes += value;
		}

		info.last_recv_ret = value;
		info.last_recv_ts = current_tick();
	}

	info.last_errcode = err;

	if(ev > 0){

		if(info.has_sock_info == 0){
			struct sockaddr_in serv, guest;  
			char serv_ip[20] = {0};  
			socklen_t serv_len = sizeof(serv);	
			getsockname(fd, (struct sockaddr *)&serv, &serv_len);  
			inet_ntop(AF_INET, &serv.sin_addr, serv_ip, sizeof(serv_ip));	
			
			char buff[200];
			int cur_pos = sprintf(buff, " (%s:%p %s:%p) ",	serv_ip, ntohs(serv.sin_port));		
			getpeername(fd, (struct sockaddr *)&serv, &serv_len);  
			inet_ntop(AF_INET, &serv.sin_addr, serv_ip, sizeof(serv_ip));	
			sprintf(buff + cur_pos, " (%s:%p %s:%p) ",	serv_ip, ntohs(serv.sin_port));	
			
			info.sock_info = buff;
		}
	}

	if(ev == 3){
		sprintf(out_buff, "[%f] [0x%lx] fd %d %s snd %d rcv %d e_s_ret %d e_r_ret %d e_s_ts %f e_r_ts %f b_ts %f e_ts %f e_err %d", current_tick(), pthread_self(),
			fd, info.sock_info.c_str(), info.send_bytes, info.recv_bytes, info.last_send_ret, info.last_recv_ret, info.last_send_ts, info.last_recv_ts, info.create_ts,current_tick(),info.last_errcode);

		g_net_stat_map.erase(fd);
	}

	if(ev == 0){
		sprintf(out_buff,"[%f] [0x%lx] socket create fd %d",  current_tick(), pthread_self(),fd);
	}

	if(ev == 4){
		sprintf(out_buff,"[%f] [0x%lx] socket accept fd %d",  current_tick(), pthread_self(),fd);
	}

	pthread_mutex_unlock(&g_mutex);

	if(out_buff != NULL){
		ffi_log_out(out_buff);
	}
}


