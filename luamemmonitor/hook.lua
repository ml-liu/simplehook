

local total_size = 0


local g_f = nil


local cnt = 0

function hook_notify(tid,block,osize,nsize)


   if(g_f == nil)
   then 
      g_f = io.open(string.format("/home/liumaliang/%x",tid),'w')
    
   end


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


function gc_step_notify(a)
   print("gc_step")
  
end

if set_hook
then
   set_hook(0x15405e0,0,"hook_notify"); --0x15405e0为luaM_realloc_的地址，可使用readelf来获取
end