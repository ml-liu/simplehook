# simplehook
hook tool, used by myself..

# compile
```cpp
cd LuaJIT-2.0.5
make
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

拷贝下述文件到应用程序目录
simplehook_64.so
netmonitor/hook.lua
libnetstat_plugin.so  //网络监控扩展模块，hook.lua中使用ffi调用

export LD_LIBRARY_PATH=.
LD_PRELOAD=./simplehook_64.so ./Server
```

# result
应用程序目录会生成simplehook.log

