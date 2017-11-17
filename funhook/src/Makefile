srcdir = .
top_srcdir = ..
top_builddir = ..

DISTORM3_DIR = $(top_srcdir)/distorm
VPATH = $(DISTORM3_DIR)/src:$(top_srcdir)/include

CC = gcc
CFLAGS = -g -O2 -Wall -fvisibility=hidden -fPIC -g -I. -I$(top_srcdir)/include -I$(DISTORM3_DIR)/include
LIBS = -ldl
LINK_SHARED = $(CC) -shared

#LIBS += -lpsapi
#LDFLAGS += -install_name @rpath/libfunchook.dylib

FUNCHOOK_OBJS = \
	os_func.o \
	os_func_unix.o \
	printf_base.o \
	funchook.o \
	funchook_io.o \
	funchook_x86.o \
	funchook_unix.o

FUNCHOOK_OBJS += funchook_syscall.o
#FUNCHOOK_OBJS += funchook_syscall.o

DISTORM3_OBJS = \
	mnemonics.o \
	wstring.o \
	textdefs.o \
	prefix.o \
	operands.o \
	insts.o \
	instructions.o \
	distorm.o \
	decoder.o

HEADERS = \
	funchook.h \
	funchook_internal.h \
	os_func.h

OBJS = $(FUNCHOOK_OBJS) $(DISTORM3_OBJS)

all: libfunchook.so

check:
	cd ../test && $(MAKE) check

libfunchook.so: $(OBJS)
	$(LINK_SHARED) $(LDFLAGS) -o libfunchook.so $(OBJS) $(LIBS)

funchook.o: funchook.c $(HEADERS)
funchook_linux.o: funchook_linux.c $(HEADERS)
funchook_windows.o: funchook_windows.c $(HEADERS)
funchook_x86.o: funchook_x86.c $(HEADERS)
os_func.o: os_func.c os_func.h printf_base.h
printf_base.o: printf_base.c printf_base.h
	$(CC) $(CFLAGS) -c -o $@ $< -DPFB_NO_EXTERNAL_FUNC -DPFB_MSVC_FORMAT

# suppress warning: missing braces around initializer [-Wmissing-braces]
insts.o: insts.c
	$(CC) $(CFLAGS) -c -o $@ $< -Wno-missing-braces

clean:
	$(RM) libfunchook.so $(OBJS)

Makefile config.h: $(srcdir)/Makefile.in $(srcdir)/config.h.in $(top_builddir)/config.status
	cd $(top_builddir) && ./config.status
