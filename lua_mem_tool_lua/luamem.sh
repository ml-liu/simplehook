lua_newstate=`readelf -a $1 | grep lua_newstate | head -n 1|awk '{print $2}'`
lua_getstack=`readelf -a $1 | grep lua_getstack  | head -n 1|awk '{print $2}'`
lua_getinfo=`readelf -a $1 |grep lua_getinfo  | head -n 1|awk '{print $2}'`
lua_sethook=`readelf -a $1 | grep lua_sethook  | head -n 1|awk '{print $2}'`
lua_tocfunction=`readelf -a $1 | grep lua_tocfunction  | head -n 1|awk '{print $2}'`
lua_settop=`readelf -a $1 | grep lua_settop  | head -n 1|awk '{print $2}'`
luaD_rawrunprotected=`readelf -a $1 | grep luaD_rawrunprotected  | head -n 1|awk '{print $2}'`


ll_require=`readelf -a $1 | grep ll_require  | head -n 1|awk '{print $2}'`
luaL_checklstring=`readelf -a $1 | grep luaL_checklstring  | head -n 1|awk '{print $2}'`
searcher_Lua=`readelf -a $1 | grep searcher_Lua  | head -n 1|awk '{print $2}'`

echo "local soaddr  = 0"
echo "lua_newstate=0x$lua_newstate"
echo "lua_getstack=0x$lua_getstack"
echo "lua_getinfo=0x$lua_getinfo"
echo "lua_sethook=0x$lua_sethook"
echo "lua_tocfunction=0x$lua_tocfunction"
echo "lua_settop=0x$lua_settop"
echo "ll_require=0x$ll_require"
echo "luaL_checklstring=0x$luaL_checklstring"
echo "luaD_rawrunprotected=0x$luaD_rawrunprotected"
echo "searcher_Lua=0x$searcher_Lua"

echo "if(hook_lua_mem)"
echo "then"
echo "    hook_lua_mem(searcher_Lua + soaddr, luaD_rawrunprotected + soaddr, luaL_checklstring+soaddr, ll_require+soaddr, lua_settop + soaddr, lua_tocfunction + soaddr,lua_newstate + soaddr,lua_getstack + soaddr,lua_getinfo + soaddr, lua_sethook + soaddr)"
echo "end"


