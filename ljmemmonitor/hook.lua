print("hook init 1111");




if(get_so_load_base)
then
local a = get_so_load_base("/home/jx3/server/bin64/x.so")
print(a)
local addr = a + 0x5f790 

local newstate = a + 0x48960

local memfun = a + 0x58210
print(string.format("%x-%x", newstate, memfun));
if(hook_luajit_mem)      
then
   hook_luajit_mem(newstate)
end

if(set_hook)
then
   set_hook(0x5290b0, "vP", "active")
end

end


local g_f1 = nil
function active(p)
    if(g_f1 == nil)
    then
       g_f1 = io.open("/tmp/xxx.lua", "w");
    end

    g_f1:write(get_current_stack()) 

    g_f1:flush()
    print("frame")
end



function lj_alloc_f1(tid,block,osize,nsize)

   print(get_current_stack())
   print(string.format("thread:%x,block=%d,osize=%d nsize=%d", tid,block,osize,nsize));
end


function hook_notify2(tid)
   print("hoookkkk")
end


hook_notify2(1)


local total_size = 0


local g_f = nil


local cnt = 0

function lj_alloc_f(tid,block,osize,nsize)



   total_size = total_size + nsize

   total_size = total_size - osize

   if(cnt >= 1000)
   then
      print(string.format("luastate ptr:0x%x, mem size=%d",tid,total_size))
      cnt = 0
   end

   cnt = cnt + 1
   return


end
