
local g_f = nil

function writelog(str)
   if(g_f == nil and get_tid)
   then
      g_f = io.open(string.format("/tmp/simplehook_thread_%x",get_tid()),'w')
   end

   print(str)

   if g_f
   then 
       g_f:write(str)
       g_f:write("\n")
   end
end


writelog("hook init");


local frame_idx = 0;





function frame_notify()
   profiler_frame(frame_idx, 0);
   frame_idx = frame_idx + 1;
end
   

function listen(a,b)
   local str =   string.format("listen %d %d",a,b);

   writelog(str);
   
end


function recv(fd,buf,len,flags)
   writelog(string.format("recv fd %d len %d flags %d", fd, len, flags))
end


function send(fd, buf, len, flags)
   writelog(string.format("send fd %d len %d flags %d", fd, len, flags))

end


function connect(fd, d1, d2)
   writelog(string.format("connect fd %d", fd))
   
end


function accept(fd, d1, d2)
  writelog(string.format("accept fd %d", fd))
end



if(start_luaprofiler)
then
  --local a = get_so_load_base("/home/test/server/bin64/x.so")
  --start_luaprofiler(0x49330 + a)
end


writelog("sdfsdfsdfsfd")

if(set_hook)
then
--   set_hook(0x5290b0,"vP","frame_notify")
   
      
  writelog("yeap");
  local l=get_fun_addr("listen")
  writelog("yeap");

  
  writelog(string.format("listen:%x",l))
  writelog("yeap");
  
  set_hook(l, "iii", "listen")
 
  set_hook(get_fun_addr("send"),"LIPLI","send")
  set_hook(get_fun_addr("recv"),"LIPLI","recv")
  set_hook(get_fun_addr("accept"),"IIPP","accept")
  set_hook(get_fun_addr("connect"),"IIPP","connect")
end

