#all: SimplePreload_64.so SimplePreload_32.so
all: simplehook.so

simplehook.so: main.c
	gcc -c -g  -m64 -Wno-missing-braces -D_GNU_SOURCE -DPFB_NO_EXTERNAL_FUNC -Ifunhook/include -Ifunhook/distorm/include -fPIC queue.c common.c BoundedPriQueue.c funhook/src/os_func.c funhook/src/os_func_unix.c funhook/src/funchook_syscall.S funhook/src/printf_base.c funhook/src/funchook.c funhook/src/funchook_io.c funhook/src/funchook_x86.c funhook/src/funchook_unix.c funhook/distorm/src/mnemonics.c funhook/distorm/src/wstring.c funhook/distorm/src/textdefs.c funhook/distorm/src/prefix.c funhook/distorm/src/operands.c funhook/distorm/src/insts.c funhook/distorm/src/instructions.c funhook/distorm/src/distorm.c funhook/distorm/src/decoder.c
	ar -r libcommon.a common.o decoder.o distorm.o funchook_io.o funchook.o funchook_syscall.o funchook_unix.o funchook_x86.o instructions.o insts.o mnemonics.o operands.o os_func.o os_func_unix.o prefix.o printf_base.o queue.o textdefs.o wstring.o BoundedPriQueue.o
	gcc -fPIC -Ilibffcall-2.0 -Ilibffcall-2.0/callback/vacall_r -Ilibffcall-2.0/callback -Ilibffcall-2.0/avcall -ILuaJIT-2.0.5/src -Ifunhook/include -Ifunhook/distorm/include -g -shared -fPIC -fvisibility=hidden -m64 -Wno-missing-braces -D_GNU_SOURCE -DPFB_NO_EXTERNAL_FUNC -DPFB_MSVC_FORMAT  -o simplehook_64.so main.c lua_plugin.c LuaJIT-2.0.5/src/libluajit.a ./libffcall-2.0/avcall/.libs/libavcall.a ./libffcall-2.0/callback/.libs/libcallback.a -ldl  -lpthread libcommon.a
	g++ -g speed_calculator.cpp netstat_plugin.cpp -o libnetstat_plugin.so --shared -fPIC libcommon.a
	  g++ -fpermissive   -Ifunhook/include -g -ILuaJIT-2.0.5/src lua_mem_tool.cpp -o liblua_mem_tool.so --shared -fPIC -fvisibility=hidden -m64 -Wno-missing-braces -D_GNU_SOURCE -DPFB_NO_EXTERNAL_FUNC -DPFB_MSVC_FORMAT libcommon.a LuaJIT-2.0.5/src/libluajit.a  -lpthread -ldl -lm
	  g++ -fpermissive   -Ifunhook/include -g -ILuaJIT-2.0.5/src lua_str_watch.cpp -o liblua_str_watch.so --shared -fPIC -fvisibility=hidden -m64 -Wno-missing-braces -D_GNU_SOURCE -DPFB_NO_EXTERNAL_FUNC -DPFB_MSVC_FORMAT libcommon.a LuaJIT-2.0.5/src/libluajit.a  -lpthread -ldl -lm	  
	gcc demo.c simplehook_64.so -lm LuaJIT-2.0.5/src/libluajit.a simplehook_64.so -I ./LuaJIT-2.0.5/src/ -ldl -lpthread libcommon.a

clean:
	rm -rf *.o
	rm -rf *.so



