print("hook init 1111");


local soaddr  = 0 ---get_so_load_base("xxx.so")



local lua_newstate = 0x19300a0
local lua_getstack = 0x0
local lua_getinfo = 0x0
local lua_sethook = 0x0
if(hook_luajit_mem)      
then
   hook_luajit_mem(lua_newstate + soaddr,lua_getstack + soaddr,lua_getinfo + soaddr, lua_sethook + soaddr)
end

