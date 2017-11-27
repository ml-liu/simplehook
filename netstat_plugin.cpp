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

#include "speed_calculator.h"



class ConnectInfo{
public:
	ConnectInfo():send_bytes(0),recv_bytes(0),last_send_errcode(0),last_recv_errcode(0),close_reason(0),create_ts(0),recv_error_cnt(0),send_error_cnt(0),send_cnt(0),recv_cnt(0),
		last_recv_ret(0),last_send_ret(0), has_sock_info(0){

		create_ts = current_tick();
	};


public:	
	int send_bytes;
	int recv_bytes;
	int last_recv_errcode;
	int last_send_errcode;
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
	std::string remote_ip;
	int local_port;

	std::string remote_info;
};


struct NetSpeedInfo{
	NetSpeedInfo(){
		spd_out = new speed_calculator(20,50, 1);
		spd_in = new  speed_calculator(20,50, 1);		
	}
	speed_calculator* spd_out;
	speed_calculator* spd_in;
};

static std::map<int, ConnectInfo> g_net_stat_map;

static pthread_mutex_t g_mutex;

static std::map<int,  NetSpeedInfo> g_port_speed_cal;
static std::map<std::string, NetSpeedInfo> g_ip_speed_cal;
static std::map<std::string, NetSpeedInfo> g_ip_port_speed_cal;
NetSpeedInfo g_total_speed_cal;


void update_speed(const ConnectInfo& info, int ev, long val){
	
	if(g_port_speed_cal.find(info.local_port) != g_port_speed_cal.end()){

		NetSpeedInfo& spdInfo = g_port_speed_cal[info.local_port];

		if(ev == 1)
			spdInfo.spd_out->add_bytes(val);
		else
			spdInfo.spd_in->add_bytes(val);
	}

	if(g_ip_speed_cal.find(info.remote_ip) != g_ip_speed_cal.end()){

		NetSpeedInfo& spdInfo = g_ip_speed_cal[info.remote_ip];

		if(ev == 1)
			spdInfo.spd_out->add_bytes(val);
		else
			spdInfo.spd_in->add_bytes(val);
	}

	if(g_ip_port_speed_cal.find(info.remote_info) != g_ip_port_speed_cal.end()){

		NetSpeedInfo& spdInfo = g_ip_port_speed_cal[info.remote_info];

		if(ev == 1)
			spdInfo.spd_out->add_bytes(val);
		else
			spdInfo.spd_in->add_bytes(val);
	}	

	if(ev == 1)
		g_total_speed_cal.spd_out->add_bytes(val);
	else
		g_total_speed_cal.spd_in->add_bytes(val);

}


void* spd_stat_thread(void* d){


	while(1){

		char* out_buff = (char*)malloc(4096);
		
		int cur_pos = sprintf(out_buff, "NET***************\nNET***total out %lld total in %lld\n", g_total_speed_cal.spd_out->speed_value(), g_total_speed_cal.spd_in->speed_value());

		std::map<int,  NetSpeedInfo>::iterator port_it;
		std::map<std::string, NetSpeedInfo>::iterator ip_it;
		for(port_it = g_port_speed_cal.begin(); port_it!= g_port_speed_cal.end(); ++port_it){
			NetSpeedInfo& info = port_it->second;
			cur_pos += sprintf(out_buff + cur_pos, "NET****PORT(%d) total out %lld total in %lld\n",port_it->first, info.spd_out->speed_value(), info.spd_in->speed_value());
		}

		for(ip_it = g_ip_speed_cal.begin(); ip_it != g_ip_speed_cal.end(); ++ip_it){
			NetSpeedInfo& info = ip_it->second;
			cur_pos += sprintf(out_buff + cur_pos, "NET***IP(%s) total out %lld total in %lld\n",ip_it->first.c_str(), info.spd_out->speed_value(), info.spd_in->speed_value());
		}
		for(ip_it = g_ip_port_speed_cal.begin(); ip_it != g_ip_port_speed_cal.end(); ++ip_it){
			NetSpeedInfo& info = ip_it->second;
			cur_pos += sprintf(out_buff + cur_pos, "NET**IP_PORT(%s) total out %lld total in %lld\n",ip_it->first.c_str(), info.spd_out->speed_value(), info.spd_in->speed_value());
		}		

		cur_pos += sprintf(out_buff + cur_pos, "*******************************");

		ffi_log_out(out_buff);
		sleep(2);
	}
}

void __attribute__((constructor)) Init(){
	pthread_mutex_init(&g_mutex, NULL);

	char* b = (char*)malloc(20);

	sprintf(b, "net plugin init");

	ffi_log_out(b);
}


extern "C"  __attribute((visibility("default"))) void add_spd_stat(int type, const char* key){
	pthread_t id;

	static int thread_not_start = 1;
	
	if(type == 1){
		NetSpeedInfo& info = g_port_speed_cal[atoi(key)];
	}else if(type == 2 ){
		NetSpeedInfo& info = g_ip_speed_cal[key];
	}else if(type == 3){
		NetSpeedInfo& info = g_ip_port_speed_cal[key];
	}else{
		if(thread_not_start == 1)
			pthread_create(&id, NULL, spd_stat_thread, NULL);
		thread_not_start = 0;
	}
}


 extern "C"  __attribute((visibility("default"))) void add_stat(int fd,int ev, int op, long value, int err){

	char* out_buff = NULL;


	

	if(ev == 0 || ev == -1 || ev == 4){
		out_buff = (char*)malloc(1024);
	}
	
	pthread_mutex_lock(&g_mutex);

	ConnectInfo& info = g_net_stat_map[fd];

	// 0 socketcreate  1 send 2 recv -1 close 4 accept
	if(ev > 0){

		if(info.has_sock_info == 0){
			struct sockaddr_in serv, guest;  
			char serv_ip[20] = {0};  
			socklen_t serv_len = sizeof(serv);	
			getsockname(fd, (struct sockaddr *)&serv, &serv_len);  
			inet_ntop(AF_INET, &serv.sin_addr, serv_ip, sizeof(serv_ip));	
			
			char buff[200] = {0};
			
			info.local_port = ntohs(serv.sin_port);
			int cur_pos = sprintf(buff, "%s:%d ",	serv_ip, ntohs(serv.sin_port));		


			
			serv_len = sizeof(serv);	 
			memset(&serv, 0, serv_len);
			getpeername(fd, (struct sockaddr *)&serv, &serv_len);  
			inet_ntop(AF_INET, &serv.sin_addr, serv_ip, sizeof(serv_ip));	
			sprintf(buff + cur_pos, "%s:%d",	serv_ip, ntohs(serv.sin_port));	

			char* local_info = ffi_get_sock_info(fd);
			char* remote_info = ffi_get_peer_info(fd);

			info.sock_info =  std::string(local_info)  + " " + remote_info;
    		info.remote_info = remote_info;

			int pos = strchr(local_info, ':') - local_info;
			if(pos > 0 && pos < strlen(local_info) - 1)
				info.local_port = atoi(local_info + pos + 1);

			pos = strchr(remote_info, ':') - remote_info;
			if(pos > 0 && pos < strlen(remote_info) - 1){
				remote_info[pos] = '\0';
				info.remote_ip = remote_info;
			}

			info.has_sock_info = 1;
		}
	}

	

	if(ev == 1){
		if(value > 0){
			info.send_bytes += value;
			update_speed(info, ev, value);
		}

		info.last_send_ret = value;
		info.last_send_ts = current_tick();
		info.last_send_errcode = err;

		
	}else if(ev == 2){
		if(value > 0){
			info.recv_bytes += value;
			update_speed(info, ev, value);
		}

		info.last_recv_ret = value;
		info.last_recv_ts = current_tick();
		info.last_recv_errcode = err;
	}




	if(ev == -1){
		sprintf(out_buff, "[%s:%d][%f] [0x%lx] fd %d (%s) snd %d rcv %d e_s_ret %d e_r_ret %d e_s_ts %f e_r_ts %f b_ts %f e_ts %f e_snd_err %d e_rcv_err %d",info.remote_ip.c_str(), info.local_port, current_tick(), pthread_self(),
			fd, info.sock_info.c_str(), info.send_bytes, info.recv_bytes, info.last_send_ret, info.last_recv_ret, info.last_send_ts, info.last_recv_ts, info.create_ts,current_tick(),info.last_send_errcode, info.last_recv_errcode);

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


