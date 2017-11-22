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
]]


local to_int=ffi.typeof("int")


function writelog(str)
   log_out(str)
end


writelog("hook init");
 
   

function listen(a,b)
   local str =  ffi.C.malloc(256);
   print(a)
   ffi.C.sprintf(str,"[%f] [0x%lx] listen ffi %d %d",ffi.C.current_tick(),ffi.C.ffi_get_tid(),to_int( a), to_int(b))
   ffi.C.ffi_log_out(str)
end


listen(11,22)

function recv(fd,buf,len,flags,ret,elaps)
   local isnonblock = is_sock_nonblock(fd)
   local buff = ffi.C.malloc(356)
   local sockinfo = ffi.C.ffi_get_sock_info(to_int(fd))
   ffi.C.sprintf(buff, "[%f] [0x%lx] recv fd %d len %d flags %d ret %d elaps %d us (%s %s) isnonblock %d",ffi.C.current_tick(),ffi.C.ffi_get_tid(),to_int(fd), to_int( len), to_int(flags), to_int(ret), to_int(elaps), sockinfo, ffi.C.ffi_get_peer_info(to_int(fd)) ,to_int(isnonblock))
   ffi.C.ffi_log_out(buff)
end


function send(fd, buf, len, flags, ret, elaps)
   local isnonblock = is_sock_nonblock(fd)
   local buff = ffi.C.malloc(356)
   local sockinfo = ffi.C.ffi_get_sock_info(to_int(fd))
   ffi.C.sprintf(buff, "[%f] [0x%lx] send fd %d len %d flags %d ret %d elaps %d us (%s %s) isnonblock %d",ffi.C.current_tick(),ffi.C.ffi_get_tid(), to_int(fd), to_int( len), to_int(flags), to_int(ret), to_int(elaps), sockinfo, ffi.C.ffi_get_peer_info(to_int(fd)) ,to_int(isnonblock))
  ffi.C.ffi_log_out(buff)
end


function connect(fd, d1, d2, ret , elaps)
   local buff = ffi.C.malloc(256)
   ffi.C.sprintf(buff, "[%f] [0x%lx] connect fd %d ret %d elaps",ffi.C.current_tick(),ffi.C.ffi_get_tid(), to_int(fd), to_int(ret), to_int(elaps))
   ffi.C.ffi_log_out(buff)   
end


function accept(fd, d1, d2, ret, elaps)
   local isnonblock = is_sock_nonblock(fd)
   local buff = ffi.C.malloc(256)
   ffi.C.sprintf(buff, "[%f] [0x%lx] accept fd %d (%s) ret %d  elaps %d isnonblock %d",ffi.C.current_tick(),ffi.C.ffi_get_tid(), to_int(ret), ffi.C.ffi_get_sock_info(to_int(fd)), to_int(ret), to_int(elaps), to_int(isnonblock))
   ffi.C.ffi_log_out(buff)
end


function socket(d,t,p,ret,elaps)
   local buff = ffi.C.malloc(256)
   ffi.C.sprintf(buff, "[%f] [0x%lx] socket domain %d type %d protocal %d ret %d elaps %d us",ffi.C.current_tick(),ffi.C.ffi_get_tid(), to_int(d), to_int(t),to_int(p), to_int(ret), to_int(elaps))
   ffi.C.ffi_log_out(buff)
end


function close(fd)
  local buff = ffi.C.malloc(256)
  ffi.C.sprintf(buff, "[%f] [0x%lx] close fd %d",ffi.C.current_tick(),ffi.C.ffi_get_tid(), to_int(fd))
  ffi.C.ffi_log_out(buff)
end



if(set_hook)
then
  local l=get_fun_addr("listen")
  
  set_hook(l, "iii", "listen")
 
  set_hook(get_fun_addr("send"),"LiPLi","send")
  set_hook(get_fun_addr("recv"),"LiPLi","recv")
  set_hook(get_fun_addr("accept"),"iiPP","accept")
  set_hook(get_fun_addr("connect"),"iiPP","connect")
  set_hook(get_fun_addr("socket"),"iiii","socket")
  set_hook(get_fun_addr("close"),"ii","close")
end

