print("hook init 1111");



local lua_newstate = 0x19300a0
local lua_getstack = 0x0
local lua_getinfo = 0x0
local lua_sethook = 0x0
if(hook_luajit_mem)      
then
   hook_luajit_mem(lua_newstate,lua_getstack,lua_getinfo, lua_sethook)
end

