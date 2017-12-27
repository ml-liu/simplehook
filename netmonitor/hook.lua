local ffi = require "ffi"
ffi.cdef[[
	int sprintf(const char* fmt, ...);
	void* malloc(size_t size);
	int printf(const char* fmt, ...);
	void ffi_log_out(char* str);
	char* ffi_get_sock_info(int fd);
	char* ffi_get_peer_info(int fd);
	double current_tick();
	long ffi_get_tid();	
	void add_stat(int fd,int ev, int op, long value, int err);
	void add_spd_stat(int type, const char* key);
]]

local need_detail_log = 0


local to_int=ffi.typeof("int")
local to_long = ffi.typeof("long")


function writelog(str)
   log_out(str)
end


writelog("hook init");
 
local netstat = ffi.load("netstat_plugin")


netstat.add_spd_stat(1, "3111")
netstat.add_spd_stat(2, "10.20.76.55")
netstat.add_spd_stat(3, "10.20.76.55:3111")
netstat.add_spd_stat(0, "")



function listen(a,b)
   local str =  ffi.C.malloc(256);
   ffi.C.sprintf(str,"[%f] [0x%lx] listen ffi %d %d",ffi.C.current_tick(),ffi.C.ffi_get_tid(),to_int( a), to_int(b))
   ffi.C.ffi_log_out(str)
end



function recv(fd,buf,len,flags,ret,elaps, errcode)

   netstat.add_stat(to_int(fd), 2, 0, to_long(ret), to_int(errcode));

   if (need_detail_log ~= 1)
   then
	   return
   end

   local isnonblock = is_sock_nonblock(fd)
   local buff = ffi.C.malloc(356)
   local sockinfo = ffi.C.ffi_get_sock_info(to_int(fd))
   ffi.C.sprintf(buff, "[%f] [0x%lx] recv fd %d len %d flags %d ret %ld elaps %d us (%s %s) isnonblock %d errcode %d",ffi.C.current_tick(),ffi.C.ffi_get_tid(),to_int(fd), to_int( len), to_int(flags), to_long(ret), to_int(elaps), sockinfo, ffi.C.ffi_get_peer_info(to_int(fd)) ,to_int(isnonblock), to_int(errcode))
   ffi.C.ffi_log_out(buff)
end
function write(fd,buf,len,flags,ret,elaps, errcode)

   netstat.add_stat(to_int(fd), 2, 0, to_long(ret), to_int(errcode));

   if (need_detail_log ~= 1)
   then
	   return
   end

   local isnonblock = is_sock_nonblock(fd)
   local buff = ffi.C.malloc(356)
   local sockinfo = ffi.C.ffi_get_sock_info(to_int(fd))
   ffi.C.sprintf(buff, "[%f] [0x%lx] recv fd %d len %d flags %d ret %ld elaps %d us (%s %s) isnonblock %d errcode %d",ffi.C.current_tick(),ffi.C.ffi_get_tid(),to_int(fd), to_int( len), to_int(flags), to_long(ret), to_int(elaps), sockinfo, ffi.C.ffi_get_peer_info(to_int(fd)) ,to_int(isnonblock), to_int(errcode))
   ffi.C.ffi_log_out(buff)
end

function send(fd, buf, len, flags, ret, elaps, errcode)
   netstat.add_stat(to_int(fd), 1, 0, to_long(ret), to_int(errcode));


   if (need_detail_log ~= 1)
   then
	   return
   end

   local isnonblock = is_sock_nonblock(fd)
   local buff = ffi.C.malloc(356)
   local sockinfo = ffi.C.ffi_get_sock_info(to_int(fd))
   ffi.C.sprintf(buff, "[%f] [0x%lx] send fd %d len %d flags %d ret %ld elaps %d us (%s %s) isnonblock %d errcode %d",ffi.C.current_tick(),ffi.C.ffi_get_tid(), to_int(fd), to_int( len), to_int(flags), to_long(ret), to_int(elaps), sockinfo, ffi.C.ffi_get_peer_info(to_int(fd)) ,to_int(isnonblock), to_int(errcode))
   ffi.C.ffi_log_out(buff)
end


function connect(fd, d1, d2, ret , elaps, errcode)
   local buff = ffi.C.malloc(256)
   ffi.C.sprintf(buff, "[%f] [0x%lx] connect fd %d ret %d elaps %d us errcode %d",ffi.C.current_tick(),ffi.C.ffi_get_tid(), to_int(fd), to_long(ret), to_int(elaps), to_int(errcode))
   ffi.C.ffi_log_out(buff)   
end


function accept(fd, d1, d2, ret, elaps)
   if (ret ~= -1) 
   then
      netstat.add_stat(to_int(ret),4, 0, 0, 0);
   end

   if (need_detail_log ~= 1)
   then
	   if (ret == -1)
	   then
	   		return
	   end
   end

   local isnonblock = is_sock_nonblock(fd)
   local buff = ffi.C.malloc(256)
   ffi.C.sprintf(buff, "[%f] [0x%lx] accept fd %d (%s) ret %d  elaps %d isnonblock %d",ffi.C.current_tick(),ffi.C.ffi_get_tid(), to_int(ret), ffi.C.ffi_get_sock_info(to_int(fd)), to_int(ret), to_int(elaps), to_int(isnonblock))
   ffi.C.ffi_log_out(buff)
end


function socket(d,t,p,ret,elaps)
   if (ret ~= -1) 
   then
	  netstat.add_stat(to_int(ret), 0, 0, 0, 0);
   end

   local buff = ffi.C.malloc(256)
   ffi.C.sprintf(buff, "[%f] [0x%lx] socket domain %d type %d protocal %d ret %d elaps %d us",ffi.C.current_tick(),ffi.C.ffi_get_tid(), to_int(d), to_int(t),to_int(p), to_int(ret), to_int(elaps))
   ffi.C.ffi_log_out(buff)
end


function close(fd)
  netstat.add_stat(to_int(fd), -1, 0, 0, 0);
  local buff = ffi.C.malloc(256)
  ffi.C.sprintf(buff, "[%f] [0x%lx] close fd %d",ffi.C.current_tick(),ffi.C.ffi_get_tid(), to_int(fd))
  ffi.C.ffi_log_out(buff)
end

function epoll_create(size, ret)
  local buff = ffi.C.malloc(256)
  ffi.C.sprintf(buff, "[%f] [0x%lx] epoll_create size %d ret %d",ffi.C.current_tick(),ffi.C.ffi_get_tid(), to_int(size), to_int(ret));
  ffi.C.ffi_log_out(buff)
end

function epoll_ctl(epfd, op , fd, ev)
  local buff = ffi.C.malloc(256)
  ffi.C.sprintf(buff, "[%f] [0x%lx] epoll_ctl epfd %d op %d fd %d ev 0x%lx",ffi.C.current_tick(),ffi.C.ffi_get_tid(), to_int(epfd), to_int(op), to_int(fd), ffi.typeof("long")(get_epoll_event_type(ev)));
  ffi.C.ffi_log_out(buff)
end

if(set_hook)
then
  local l=get_fun_addr("listen")
  
  set_hook(l, "iii", "listen")
 
  set_hook(get_fun_addr("send"),"liPLi","send")
  set_hook(get_fun_addr("recv"),"liPLi","recv")
  set_hook(get_fun_addr("accept"),"iiPP","accept")
  set_hook(get_fun_addr("connect"),"iiPP","connect")
  set_hook(get_fun_addr("socket"),"iiii","socket")
  set_hook(get_fun_addr("close"),"ii","close")
  set_hook(get_fun_addr("epoll_create"),"ii","epoll_create")
  set_hook(get_fun_addr("epoll_ctl"),"iiiiP","epoll_ctl")  

end

