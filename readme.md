# simplehook
hook tool, used by myself..

# compile
```cpp
cd LuaJIT-2.0.5
make linux
cd ..
cd libffcall-2.0
chmod a+x ./configure
./configure --with-pic
make
cd ..
make
```
# run
```cpp
simplehook_64.so
hook.lua
libnetstat_plugin.so  //网络监控扩展模块，hook.lua中使用ffi调用

export LD_LIBRARY_PATH=.
LD_PRELOAD=./simplehook_64.so ./Server
```

# result
/tmp/simplehook_thread_*

