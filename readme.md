# simplehook
hook tool, used by myself..

# compile
```cpp
cd lua-5.1.5
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

LD_PRELOAD=./simplehook_64.so ./Server
```

# result
/tmp/simplehook_thread_*

