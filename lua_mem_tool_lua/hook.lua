print("hook init 1111");



local newstate = 0x19300a0

if(hook_luajit_mem)      
then
   hook_luajit_mem(newstate,0x192fa70,0x192fa60, 0x1930cb0)
end



local total_size = 0


local last_total_size = 0

local g_f = nil


local cnt = 0

local lasttime = os.time()

function lj_alloc_f(tid,block,osize,nsize)
   
   if(g_f == nil)
   then 
      g_f = io.open(string.format("/tmp/ljmem_%x",tid),'w')
    
   end

   total_size = total_size + nsize

   total_size = total_size - osize

   if(cnt > 1000 or   (total_size - last_total_size) > 1000000)
   then
      g_f:write(string.format("luastate ptr:0x%x, mem size=%d\n",tid,total_size))
      cnt = 0
      last_total_size = total_size   
   end
   cnt = cnt+1 

   return


end
