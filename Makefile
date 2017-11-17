#all: SimplePreload_64.so SimplePreload_32.so
all: simplehook.so

simplehook.so: main.c
	gcc -fPIC -Ilibffcall-2.0 -Ilibffcall-2.0/callback/vacall_r -Ilibffcall-2.0/callback -Ilibffcall-2.0/avcall -Ilua-5.1.5/src -Ifunhook/include -Ifunhook/distorm/include -g -shared -fPIC -fvisibility=hidden -m64 -Wno-missing-braces -D_GNU_SOURCE -DPFB_NO_EXTERNAL_FUNC -DPFB_MSVC_FORMAT  -o simplehook_64.so main.c  funhook/src/os_func.c funhook/src/os_func_unix.c funhook/src/funchook_syscall.S funhook/src/printf_base.c funhook/src/funchook.c funhook/src/funchook_io.c funhook/src/funchook_x86.c funhook/src/funchook_unix.c funhook/distorm/src/mnemonics.c funhook/distorm/src/wstring.c funhook/distorm/src/textdefs.c funhook/distorm/src/prefix.c funhook/distorm/src/operands.c funhook/distorm/src/insts.c funhook/distorm/src/instructions.c funhook/distorm/src/distorm.c funhook/distorm/src/decoder.c  lua-5.1.5/src/liblua.a ./libffcall-2.0/avcall/.libs/libavcall.a ./libffcall-2.0/callback/.libs/libcallback.a -ldl  -lpthread
	gcc demo.c simplehook_64.so -lm lua-5.1.5/src/liblua.a simplehook_64.so -I ./lua-5.1.5/src/ -ldl -lpthread

clean:
	rm -rf *.o
	rm -rf *.so



