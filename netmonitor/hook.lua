

function writelog(str)
   log_out(str)
end


writelog("hook init");
 
   

function listen(a,b)
   local str =   string.format("listen %d %d",a,b);

   writelog(str);
   
end


function recv(fd,buf,len,flags,ret,elaps)
   local l_ip,l_port = get_sock_info(fd)
   local ip,port = get_peer_info(fd)
   local isnonblock = is_sock_nonblock(fd)

   writelog(string.format("recv fd %d len %d flags %d ret %d elaps %d us (%s:%d %s:%d) isnonblock %d", fd, len, flags, ret, elaps, l_ip,l_port,ip,port, isnonblock))
end


function send(fd, buf, len, flags, ret, elaps)
   local l_ip,l_port = get_sock_info(fd)
   local ip,port = get_peer_info(fd)
   local isnonblock = is_sock_nonblock(fd)

   writelog(string.format("send fd %d len %d flags %d, ret %d elaps %d us  (%s:%d %s:%d) isnonblock %d", fd, len, flags, ret, eplaps, l_ip,l_port,ip,port, isnonblock))

end


function connect(fd, d1, d2, ret , elaps)
   writelog(string.format("connect fd %d ret %d elaps", fd, ret, elaps))
   
end


function accept(fd, d1, d2)
  local l_ip,l_port = get_sock_info(fd)
  local isnonblock = is_sock_nonblock(fd)
  writelog(string.format("accept fd %d (%s:%d) isnonblock %d", fd, l_ip,l_port,isnonblock))
end


function socket(d,t,p,ret,elaps)
  writelog(string.format("socket domain %d type %d protocal %d ret %d elaps %d us", d,t,p,ret,elaps)) 
end


function close(fd)
  writelog(string.format("close fd %d", fd))
end



if(set_hook)
then
   
      
  local l=get_fun_addr("listen")
  
  set_hook(l, "iii", "listen")
 
  set_hook(get_fun_addr("send"),"LIPLI","send")
  set_hook(get_fun_addr("recv"),"LIPLI","recv")
  set_hook(get_fun_addr("accept"),"IIPP","accept")
  set_hook(get_fun_addr("connect"),"IIPP","connect")
  set_hook(get_fun_addr("socket"),"IIII","socket")
  set_hook(get_fun_addr("close"),"II","close")
end

