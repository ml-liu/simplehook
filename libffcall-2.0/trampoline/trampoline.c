/* Trampoline construction */

/*
 * Copyright 1995-2017 Bruno Haible <bruno@clisp.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "config.h"
#include "trampoline.h"

#if defined(__hppa__) && !defined(__hppa64__)
#if 0
#define __hppaold__  /* Old trampoline, real machine code. */
#else
#define __hppanew__  /* New trampoline, just a closure. */
#endif
#endif
#if defined(__hppa64__)
#if 0
#define __hppa64old__  /* Old trampoline, real machine code. */
#else
#define __hppa64new__  /* New trampoline, just a closure. */
#endif
#endif
#if defined(__powerpc__) && !defined(__powerpc64__)
#if !defined(_AIX)
#define __powerpcsysv4__  /* SysV.4 ABI, real machine code. */
#else
#define __powerpcaix__  /* AIX ABI, just a closure. */
#endif
#endif
#if defined(__powerpc64__) && !defined(__powerpc64_elfv2__)
#define __powerpc64aix__  /* AIX ABI, just a closure. */
#endif
#if defined(__hppanew__) || defined(__hppa64new__)
/*
 * A function pointer is a biased pointer to a data area whose first word
 * (hppa) or third word (hppa64) contains the actual address of the function.
 */
extern void tramp (); /* trampoline prototype */
/* We don't need to take any special measures to make the code executable
 * since the actual instructions are in the text segment.
 */
#ifndef CODE_EXECUTABLE
#define CODE_EXECUTABLE
#endif
#endif
#if defined(__powerpcaix__) || defined(__powerpc64aix__) || defined(__ia64__)
/*
 * A function pointer is a pointer to a data area whose first word contains
 * the actual address of the function.
 */
extern void (*tramp) (); /* trampoline prototype */
/* We don't need to take any special measures to make the code executable
 * since the actual instructions are in the text segment.
 */
#ifndef CODE_EXECUTABLE
#define CODE_EXECUTABLE
#endif
#endif

#ifndef CODE_EXECUTABLE
  /* How do we make the trampoline's code executable? */
  #if defined(HAVE_MACH_VM) || defined(HAVE_WORKING_MPROTECT)
    #if HAVE_MPROTECT_AFTER_MALLOC_CAN_EXEC > 0
      /* mprotect() [or equivalent] the malloc'ed area. */
      #define EXECUTABLE_VIA_MALLOC_THEN_MPROTECT
    #elif HAVE_MPROTECT_AFTER_MMAP_CAN_EXEC > 0
      /* mprotect() [or equivalent] the mmap'ed area. */
      #define EXECUTABLE_VIA_MMAP_THEN_MPROTECT
    #elif defined(HAVE_MMAP_SHARED_CAN_EXEC)
      #define EXECUTABLE_VIA_MMAP_FILE_SHARED
    #else
      #error "Don't know how to make memory pages executable."
    #endif
  #else
    #ifdef HAVE_MMAP
      /* Use an mmap'ed page. */
      #define EXECUTABLE_VIA_MMAP
    #else
      #ifdef HAVE_SHM
        /* Use an shmat'ed page. */
        #define EXECUTABLE_VIA_SHM
      #else
        #if (defined(_WIN32) || defined(__WIN32__)) && ! defined(__CYGWIN__) /* native Windows */
          #define EXECUTABLE_VIA_VIRTUALALLOC
        #else
          ??
        #endif
      #endif
    #endif
  #endif
#endif

#include <stdio.h> /* declares fprintf() */

#include <sys/types.h>
#include <stdlib.h> /* declares abort(), malloc(), free() */
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

/* Define intptr_t, uintptr_t. */
#include <stdint.h>

/* Declare getpagesize(). */
#ifdef HAVE_GETPAGESIZE
#ifdef __cplusplus
extern "C" RETGETPAGESIZETYPE getpagesize (void);
#else
extern RETGETPAGESIZETYPE getpagesize (void);
#endif
#else
#ifdef HAVE_SYS_PARAM_H
#include <sys/param.h>
#else
/* Not Unix, e.g. mingw32 */
#define PAGESIZE 4096
#endif
#define getpagesize() PAGESIZE
#endif

/* Declare mprotect() or equivalent. */
#if defined(EXECUTABLE_VIA_MALLOC_THEN_MPROTECT) || defined(EXECUTABLE_VIA_MMAP_THEN_MPROTECT)
#ifdef HAVE_MACH_VM
#include <sys/resource.h>
#include <mach/mach_interface.h>
#ifdef __osf__
#include <mach_init.h>
#endif
#include <mach/machine/vm_param.h>
#else
#include <sys/types.h>
#include <sys/mman.h>
#endif
#endif

/* Declare mmap(). */
#if defined(EXECUTABLE_VIA_MMAP) || defined(EXECUTABLE_VIA_MMAP_FILE_SHARED)
#include <sys/types.h>
#include <sys/mman.h>
#if !defined(PROT_EXEC) && defined(PROT_EXECUTE) /* Irix 4.0.5 needs this */
#define PROT_EXEC PROT_EXECUTE
#endif
#endif

/* Declare open(). */
#if defined(EXECUTABLE_VIA_MMAP_DEVZERO) || defined(EXECUTABLE_VIA_MMAP_FILE_SHARED)
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#endif

/* Declare shmget(), shmat(), shmctl(). */
#ifdef EXECUTABLE_VIA_SHM
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#ifdef HAVE_SYS_SYSMACROS_H
#include <sys/sysmacros.h>
#endif
#endif

/* Declare VirtualAlloc(), GetSystemInfo. */
#ifdef EXECUTABLE_VIA_VIRTUALALLOC
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <windows.h>
#endif

/* Some old mmap() implementations require the flag MAP_FILE whenever you pass
   an fd >= 0. */
#ifndef MAP_FILE
#define MAP_FILE 0
#endif
/* Some old mmap() implementations require the flag MAP_VARIABLE whenever you
   pass an addr == NULL. */
#ifndef MAP_VARIABLE
#define MAP_VARIABLE 0
#endif

/* Support for instruction cache flush. */
#ifdef __i386__
#if (defined(_WIN32) || defined(__WIN32__)) && ! defined(__CYGWIN__) /* native Windows */
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <windows.h>
#endif
#endif
#if defined(__mips__) || defined(__mipsn32__) || defined(__mips64__)
#ifdef HAVE_SYS_CACHECTL_H /* IRIX, Linux */
#include <sys/cachectl.h>
#else
#ifdef __OpenBSD__
#include <machine/sysarch.h>
#endif
#endif
#endif
/* Inline assembly function for instruction cache flush. */
#if defined(__sparc__) || defined(__sparc64__) || defined(__alpha__) || defined(__hppaold__) || defined(__hppa64old__) || defined(__powerpcsysv4__) || defined(__powerpc64_elfv2__)
#if defined(__sparc__) || defined(__sparc64__)
extern void __TR_clear_cache_4();
#else
extern void __TR_clear_cache();
#endif
#endif

/* Support for multithread-safe coding. */
#include "glthread/lock.h"

#if !defined(CODE_EXECUTABLE) && defined(EXECUTABLE_VIA_MMAP_FILE_SHARED)
/* Opens a file descriptor and attempts to make it non-inheritable. */
static int open_noinherit (const char *filename, int flags, int mode)
{
# if O_CLOEXEC
  return open (filename, flags | O_CLOEXEC, mode);
# else
  int fd = open (filename, flags, mode);
#  ifdef F_SETFD
  if (fd >= 0)
    {
      int flags = fcntl (fd, F_GETFD, 0);
      if (flags >= 0)
        fcntl (fd, F_SETFD, flags | FD_CLOEXEC);
    }
#  endif
  return fd;
# endif
}
#endif

/* Length and alignment of trampoline */
#ifdef __i386__
#define TRAMP_LENGTH 15
#define TRAMP_ALIGN 16  /* 4 for a i386, 16 for a i486 */
#endif
#ifdef __m68k__
#define TRAMP_LENGTH 18
#define TRAMP_ALIGN 16
#endif
#if defined(__mipsold__) && !defined(__mipsn32__)
#define TRAMP_LENGTH 32
#define TRAMP_ALIGN 4
#endif
#if (defined(__mips__) || defined(__mipsn32__)) && !defined(__mips64__)
#define TRAMP_LENGTH 36
#define TRAMP_ALIGN 4
#endif
#ifdef __mips64old__
#define TRAMP_LENGTH 84
#define TRAMP_ALIGN 4
#endif
#ifdef __mips64__
#define TRAMP_LENGTH 48
#define TRAMP_ALIGN 8
#endif
#if defined(__sparc__) && !defined(__sparc64__)
#define TRAMP_LENGTH 28
#define TRAMP_ALIGN 16
#endif
#ifdef __sparc64__
#define TRAMP_LENGTH 48
#define TRAMP_ALIGN 16
#endif
#ifdef __alpha__
#define TRAMP_LENGTH 48
#define TRAMP_ALIGN 8
#endif
#ifdef __hppaold__
#define TRAMP_LENGTH 56
#define TRAMP_ALIGN 16
#endif
#ifdef __hppanew__
#define TRAMP_LENGTH 20
#define TRAMP_ALIGN 16
#define TRAMP_BIAS 2
#endif
#ifdef __hppa64old__
#define TRAMP_LENGTH 96
#define TRAMP_ALIGN 8
#define TRAMP_BIAS 64
#endif
#ifdef __hppa64new__
#define TRAMP_LENGTH 56
#define TRAMP_ALIGN 8
#endif
#if defined(__arm__) || defined(__armhf__)
#define TRAMP_LENGTH 36
#define TRAMP_ALIGN 4
#endif
#ifdef __arm64__
#define TRAMP_LENGTH 48
#define TRAMP_ALIGN 8
#endif
#ifdef __powerpcsysv4__
#define TRAMP_LENGTH 36
#define TRAMP_ALIGN 4
#endif
#ifdef __powerpcaix__
#define TRAMP_LENGTH 24
#define TRAMP_ALIGN 4
#endif
#ifdef __powerpc64_elfv2__
#define TRAMP_LENGTH 48
#define TRAMP_ALIGN 8
#endif
#ifdef __powerpc64aix__
#define TRAMP_LENGTH 48
#define TRAMP_ALIGN 8
#endif
#ifdef __ia64__
#define TRAMP_LENGTH 40
#define TRAMP_ALIGN 16
#endif
#ifdef __x86_64__
#ifdef __x86_64_x32__
#define TRAMP_LENGTH 18
#define TRAMP_ALIGN 4
#else
#define TRAMP_LENGTH 32
#define TRAMP_ALIGN 16
#endif
#endif
#if defined(__s390__) && !defined(__s390x__)
#define TRAMP_LENGTH 40
#define TRAMP_ALIGN 4
#endif
#if defined(__s390x__)
#define TRAMP_LENGTH 64
#define TRAMP_ALIGN 8
#endif

#ifndef TRAMP_BIAS
#define TRAMP_BIAS 0
#endif

#if !defined(CODE_EXECUTABLE)
static long pagesize = 0;
#endif

#if !defined(CODE_EXECUTABLE) && (defined(EXECUTABLE_VIA_MMAP_DEVZERO) || defined(EXECUTABLE_VIA_MMAP_FILE_SHARED))

/* Variables needed for obtaining memory pages via mmap(). */
#if defined(EXECUTABLE_VIA_MMAP_DEVZERO)
static int zero_fd;
#endif
#if defined(EXECUTABLE_VIA_MMAP_FILE_SHARED)
static int file_fd;
static long file_length;
#endif

/* Initialization of these variables. */
static void for_mmap_init (void)
{
#if defined(EXECUTABLE_VIA_MMAP_DEVZERO)
  zero_fd = open("/dev/zero",O_RDONLY,0644);
  if (zero_fd < 0)
    { fprintf(stderr,"trampoline: Cannot open /dev/zero!\n"); abort(); }
#endif
#if defined(EXECUTABLE_VIA_MMAP_FILE_SHARED)
  {
    char filename[100];
    sprintf(filename, "%s/trampdata-%d-%ld", "/tmp", getpid (), random ());
    file_fd = open_noinherit (filename, O_CREAT | O_RDWR | O_TRUNC, 0700);
    if (file_fd < 0)
      { fprintf(stderr,"trampoline: Cannot open %s!\n",filename); abort(); }
    /* Remove the file from the file system as soon as possible, to make
       sure there is no leftover after this process terminates or crashes. */
    unlink(filename);
  }
  file_length = 0;
#endif
}

/* Once-only initializer for these variables. */
gl_once_define(static, for_mmap_once)

#endif

#if !defined(CODE_EXECUTABLE) && !defined(EXECUTABLE_VIA_MALLOC_THEN_MPROTECT)
/* AIX doesn't support mprotect() in malloc'ed memory. Must get pages of
 * memory with execute permission via mmap(). Then keep a free list of
 * free trampolines.
 */
static char* freelist = NULL;
/* Lock that protects the freelist from simultaneous access from multiple
   threads. */
gl_lock_define_initialized(static, freelist_lock)
#endif

trampoline_function_t alloc_trampoline (trampoline_function_t address, void** variable, void* data)
{
  char* function;
  char* function_x;

#if !defined(CODE_EXECUTABLE)
  /* First, get the page size once and for all. */
  if (!pagesize)
    {
      /* Simultaneous execution of this initialization in multiple threads
         is OK. */
#if defined(EXECUTABLE_VIA_VIRTUALALLOC)
      /* GetSystemInfo
         <https://msdn.microsoft.com/en-us/library/ms724381.aspx>
         <https://msdn.microsoft.com/en-us/library/ms724958.aspx> */
      SYSTEM_INFO info;
      GetSystemInfo(&info);
      pagesize = info.dwPageSize;
#elif defined(HAVE_MACH_VM)
      pagesize = vm_page_size;
#else
      pagesize = getpagesize();
#endif
#if defined(EXECUTABLE_VIA_MMAP_DEVZERO) || defined(EXECUTABLE_VIA_MMAP_FILE_SHARED)
      /* Use a once-only initializer here, since simultaneous execution of
         for_mmap_init() in multiple threads must be avoided. */
      gl_once (for_mmap_once, for_mmap_init);
#endif
    }
#endif

  /* 1. Allocate room */

#if !defined(CODE_EXECUTABLE) && !defined(EXECUTABLE_VIA_MALLOC_THEN_MPROTECT)
  gl_lock_lock(freelist_lock);
  if (freelist == NULL)
    { /* Get a new page. */
      char* page;
      char* page_end;
#ifdef EXECUTABLE_VIA_VIRTUALALLOC
      /* VirtualAlloc
         <https://msdn.microsoft.com/en-us/library/aa366887.aspx>
         <https://msdn.microsoft.com/en-us/library/aa366786.aspx> */
      page = VirtualAlloc(NULL,pagesize,MEM_COMMIT,PAGE_EXECUTE_READWRITE);
      if (page == NULL)
        { fprintf(stderr,"trampoline: Out of virtual memory!\n"); abort(); }
      page_end = page + pagesize;
#else
#ifdef EXECUTABLE_VIA_MMAP_FILE_SHARED
      char* page_x;
      /* Extend the file by one page. */
      long new_file_length = file_length + pagesize;
      if (ftruncate(file_fd,new_file_length) < 0)
        { fprintf(stderr,"trampoline: Cannot extend backing file!\n"); abort(); }
      /* Create separate mappings for writing and for executing. */
      page = (char*)mmap(NULL,pagesize,PROT_READ|PROT_WRITE,MAP_SHARED,file_fd,file_length);
      page_x = (char*)mmap(NULL,pagesize,PROT_READ|PROT_EXEC,MAP_SHARED,file_fd,file_length);
      if (page == (char*)(-1) || page_x == (char*)(-1))
        { fprintf(stderr,"trampoline: Out of virtual memory!\n"); abort(); }
      file_length = new_file_length;
      page_end = page + pagesize;
      /* Link the two pages together. */
      ((intptr_t*)page)[0] = page_x - page;
      page = (char*)(((uintptr_t)page + sizeof(intptr_t) + TRAMP_ALIGN-1) & -TRAMP_ALIGN);
#else
#ifdef EXECUTABLE_VIA_MMAP_THEN_MPROTECT
#ifdef HAVE_MMAP_ANONYMOUS
      /* Use mmap with the MAP_ANONYMOUS or MAP_ANON flag. */
      page = mmap(NULL, pagesize, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_VARIABLE, -1, 0);
#else
      /* Use mmap on /dev/zero. */
      page = mmap(NULL, pagesize, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_FILE | MAP_VARIABLE, zero_fd, 0);
#endif
#endif
#ifdef EXECUTABLE_VIA_MMAP
#ifdef HAVE_MMAP_ANONYMOUS
      /* Use mmap with the MAP_ANONYMOUS or MAP_ANON flag. */
      page = mmap(NULL, pagesize, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS | MAP_VARIABLE, -1, 0);
#else
      /* Use mmap on /dev/zero. */
      page = mmap(NULL, pagesize, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_FILE | MAP_VARIABLE, zero_fd, 0);
#endif
#endif
#ifdef EXECUTABLE_VIA_SHM
      int shmid = shmget(IPC_PRIVATE, pagesize, 0700|IPC_CREAT);
      if (shmid<0)
        { page = (char*)(-1); }
      else
        { page = shmat(shmid, 0, 0); shmctl(shmid, IPC_RMID, 0); }
#endif
      if (page == (char*)(-1))
        { fprintf(stderr,"trampoline: Out of virtual memory!\n"); abort(); }
      page_end = page + pagesize;
#endif
#endif
      /* Fill it with free trampolines. */
      { char** last = &freelist;
        while (page+TRAMP_LENGTH <= page_end)
          { *last = page; last = (char**)page;
            page = (char*)(((uintptr_t)page + TRAMP_LENGTH + TRAMP_ALIGN-1) & -TRAMP_ALIGN);
          }
        *last = NULL;
    } }
  function = freelist; freelist = *(char**)freelist;
  gl_lock_unlock(freelist_lock);
#else
  { char* room = (char*) malloc(sizeof(void*) + TRAMP_LENGTH + TRAMP_ALIGN-1);
    if (!room)
      { fprintf(stderr,"trampoline: Out of virtual memory!\n"); abort(); }
    function = (char*)(((uintptr_t)room + sizeof(void*) + TRAMP_ALIGN-1) & -TRAMP_ALIGN);
    ((char**)function)[-1] = room; /* backpointer for free_trampoline() */
  }
#endif

#if !defined(CODE_EXECUTABLE) && defined(EXECUTABLE_VIA_MMAP_FILE_SHARED)
  /* Find the executable address corresponding to the writable address. */
  { uintptr_t page = (uintptr_t) function & -(intptr_t)pagesize;
    function_x = function + ((intptr_t*)page)[0];
  }
#else
  function_x = function;
#endif

  /* 2. Fill out the trampoline */
#ifdef __i386__
  /* function:
   *    movl $<data>,<variable>		C7 05 <variable> <data>
   *    jmp <address>			E9 <address>-<here>
   * here:
   */
  *(short *) (function + 0) = 0x05C7;
  *(long *)  (function + 2) = (long) variable;
  *(long *)  (function + 6) = (long) data;
  *(char *)  (function +10) = 0xE9;
  *(long *)  (function +11) = (long) address - (long) (function_x + 15);
#define is_tramp(function)  \
  *(unsigned short *) (function + 0) == 0x05C7 && \
  *(unsigned char *)  (function +10) == 0xE9
#define tramp_address(function)  \
  *(long *)  (function +11) + (long) (function + 15)
#define tramp_variable(function)  \
  *(long *)  (function + 2)
#define tramp_data(function)  \
  *(long *)  (function + 6)
#endif
#ifdef __m68k__
  /* function:
   *    movel #<data>,<variable>	23 FC <data> <variable>
   *    jmp <address>			4E F9 <address>
   *    nop				4E 71
   */
  *(short *) (function + 0) = 0x23FC;
  *(long *)  (function + 2) = (long) data;
  *(long *)  (function + 6) = (long) variable;
  *(short *) (function +10) = 0x4EF9;
  *(long *)  (function +12) = (long) address;
  *(short *) (function +16) = 0x4E71;
#define is_tramp(function)  \
  *(unsigned short *) (function + 0) == 0x23FC && \
  *(unsigned short *) (function +10) == 0x4EF9 && \
  *(unsigned short *) (function +16) == 0x4E71
#define tramp_address(function)  \
  *(long *)  (function +12)
#define tramp_variable(function)  \
  *(long *)  (function + 6)
#define tramp_data(function)  \
  *(long *)  (function + 2)
#endif
#if defined(__mipsold__) && !defined(__mipsn32__)
  /* function:
   *    li $2,<data>&0xffff0000		3C 02 hi16(<data>)
   *    ori $2,$2,<data>&0xffff		34 42 lo16(<data>)
   *    sw $2,<variable>		3C 01 hi16(<variable>)
   *    				AC 22 lo16(<variable>)
   *    li $25,<address>&0xffff0000	3C 19 hi16(<address>)
   *    ori $25,$25,<address>&0xffff	37 39 lo16(<address>)
   *    j $25				03 20 00 08
   *    nop				00 00 00 00
   */
  /* What about big endian / little endian ?? */
  *(short *) (function + 0) = 0x3C02;
  *(short *) (function + 2) = (unsigned long) data >> 16;
  *(short *) (function + 4) = 0x3442;
  *(short *) (function + 6) = (unsigned long) data & 0xffff;
  *(short *) (function + 8) = 0x3C01;
  *(short *) (function +10) = (unsigned long) variable >> 16;
  *(short *) (function +12) = 0xAC22;
  *(short *) (function +14) = (unsigned long) variable & 0xffff;
  *(short *) (function +16) = 0x3C19;
  *(short *) (function +18) = (unsigned long) address >> 16;
  *(short *) (function +20) = 0x3739;
  *(short *) (function +22) = (unsigned long) address & 0xffff;
  *(long *)  (function +24) = 0x03200008;
  *(long *)  (function +28) = 0x00000000;
#define is_tramp(function)  \
  *(unsigned short *) (function + 0) == 0x3C02 && \
  *(unsigned short *) (function + 4) == 0x3442 && \
  *(unsigned short *) (function + 8) == 0x3C01 && \
  *(unsigned short *) (function +12) == 0xAC22 && \
  *(unsigned short *) (function +16) == 0x3C19 && \
  *(unsigned short *) (function +20) == 0x3739 && \
  *(unsigned long *)  (function +24) == 0x03200008 && \
  *(unsigned long *)  (function +28) == 0x00000000
#define hilo(hiword,loword)  \
  (((unsigned long) (hiword) << 16) | (unsigned long) (loword))
#define tramp_address(function)  \
  hilo(*(unsigned short *) (function +18), *(unsigned short *) (function +22))
#define tramp_variable(function)  \
  hilo(*(unsigned short *) (function +10), *(unsigned short *) (function +14))
#define tramp_data(function)  \
  hilo(*(unsigned short *) (function + 2), *(unsigned short *) (function + 6))
#endif
#if (defined(__mips__) || defined(__mipsn32__)) && !defined(__mips64__)
  /* function:
   *    lw $2,24($25)			8F 22 00 18
   *    lw $3,28($25)			8F 23 00 1C
   *    sw $3,0($2)			AC 43 00 00
   *    lw $25,32($25)			8F 39 00 20
   *    j $25				03 20 00 08
   *    nop				00 00 00 00
   *    .word <variable>		<variable>
   *    .word <data>			<data>
   *    .word <address>			<address>
   */
  *(unsigned int *) (function + 0) = 0x8F220018;
  *(unsigned int *) (function + 4) = 0x8F23001C;
  *(unsigned int *) (function + 8) = 0xAC430000;
  *(unsigned int *) (function +12) = 0x8F390020;
  *(unsigned int *) (function +16) = 0x03200008;
  *(unsigned int *) (function +20) = 0x00000000;
  *(unsigned int *) (function +24) = (unsigned int) variable;
  *(unsigned int *) (function +28) = (unsigned int) data;
  *(unsigned int *) (function +32) = (unsigned int) address;
#define TRAMP_CODE_LENGTH  24
#define is_tramp(function)  \
  *(int *)          (function + 0) == 0x8F220018 && \
  *(int *)          (function + 4) == 0x8F23001C && \
  *(int *)          (function + 8) == 0xAC430000 && \
  *(int *)          (function +12) == 0x8F390020 && \
  *(int *)          (function +16) == 0x03200008 && \
  *(int *)          (function +20) == 0x00000000
#define tramp_address(function)  \
  *(unsigned int *) (function +32)
#define tramp_variable(function)  \
  *(unsigned int *) (function +24)
#define tramp_data(function)  \
  *(unsigned int *) (function +28)
#endif
#ifdef __mips64old__
  /* function:
   *    dli $2,<variable>		3C 02 hi16(hi32(<variable>))
   *					34 42 lo16(hi32(<variable>))
   *					00 02 14 38
   *					34 42 hi16(lo32(<variable>))
   *					00 02 14 38
   *					34 42 lo16(lo32(<variable>))
   *    dli $3,<data>			3C 03 hi16(hi32(<data>))
   *					34 63 lo16(hi32(<data>))
   *					00 03 1C 38
   *					34 63 hi16(lo32(<data>))
   *					00 03 1C 38
   *					34 63 lo16(lo32(<data>))
   *    sd $3,0($2)			FC 43 00 00
   *    dli $25,<address>		3C 19 hi16(hi32(<address>))
   *					37 39 lo16(hi32(<address>))
   *					00 19 CC 38
   *					37 39 hi16(lo32(<address>))
   *					00 19 CC 38
   *					37 39 lo16(lo32(<address>))
   *    j $25				03 20 00 08
   *    nop				00 00 00 00
   */
  /* What about big endian / little endian ?? */
  *(short *) (function + 0) = 0x3C02;
  *(short *) (function + 2) = (unsigned long) variable >> 48;
  *(short *) (function + 4) = 0x3442;
  *(short *) (function + 6) = ((unsigned long) variable >> 32) & 0xffff;
  *(int *)   (function + 8) = 0x00021438;
  *(short *) (function +12) = 0x3442;
  *(short *) (function +14) = ((unsigned long) variable >> 16) & 0xffff;
  *(int *)   (function +16) = 0x00021438;
  *(short *) (function +20) = 0x3442;
  *(short *) (function +22) = (unsigned long) variable & 0xffff;
  *(short *) (function +24) = 0x3C03;
  *(short *) (function +26) = (unsigned long) data >> 48;
  *(short *) (function +28) = 0x3463;
  *(short *) (function +30) = ((unsigned long) data >> 32) & 0xffff;
  *(int *)   (function +32) = 0x00031C38;
  *(short *) (function +36) = 0x3463;
  *(short *) (function +38) = ((unsigned long) data >> 16) & 0xffff;
  *(int *)   (function +40) = 0x00031C38;
  *(short *) (function +44) = 0x3463;
  *(short *) (function +46) = (unsigned long) data & 0xffff;
  *(int *)   (function +48) = 0xFC430000;
  *(short *) (function +52) = 0x3C19;
  *(short *) (function +54) = (unsigned long) address >> 48;
  *(short *) (function +56) = 0x3739;
  *(short *) (function +58) = ((unsigned long) address >> 32) & 0xffff;
  *(int *)   (function +60) = 0x0019CC38;
  *(short *) (function +64) = 0x3739;
  *(short *) (function +66) = ((unsigned long) address >> 16) & 0xffff;
  *(int *)   (function +68) = 0x0019CC38;
  *(short *) (function +72) = 0x3739;
  *(short *) (function +74) = (unsigned long) address & 0xffff;
  *(int *)   (function +76) = 0x03200008;
  *(int *)   (function +80) = 0x00000000;
#define is_tramp(function)  \
  *(unsigned short *) (function + 0) == 0x3C02 && \
  *(unsigned short *) (function + 4) == 0x3442 && \
  *(unsigned int *)   (function + 8) == 0x00021438 && \
  *(unsigned short *) (function +12) == 0x3442 && \
  *(unsigned int *)   (function +16) == 0x00021438 && \
  *(unsigned short *) (function +20) == 0x3442 && \
  *(unsigned short *) (function +24) == 0x3C03 && \
  *(unsigned short *) (function +28) == 0x3463 && \
  *(unsigned int *)   (function +32) == 0x00031C38 && \
  *(unsigned short *) (function +36) == 0x3463 && \
  *(unsigned int *)   (function +40) == 0x00031C38 && \
  *(unsigned short *) (function +44) == 0x3463 && \
  *(unsigned int *)   (function +48) == 0xFC430000 && \
  *(unsigned short *) (function +52) == 0x3C19 && \
  *(unsigned short *) (function +56) == 0x3739 && \
  *(unsigned int *)   (function +60) == 0x0019CC38 && \
  *(unsigned short *) (function +64) == 0x3739 && \
  *(unsigned int *)   (function +68) == 0x0019CC38 && \
  *(unsigned short *) (function +72) == 0x3739 && \
  *(unsigned int *)   (function +76) == 0x03200008 && \
  *(unsigned int *)   (function +80) == 0x00000000
#define hilo(word3,word2,word1,word0)  \
  (((unsigned long) (word3) << 48) | ((unsigned long) (word2) << 32) | \
   ((unsigned long) (word1) << 16) | (unsigned long) (word0))
#define tramp_address(function)  \
  hilo(*(unsigned short *) (function +54), \
       *(unsigned short *) (function +58), \
       *(unsigned short *) (function +66), \
       *(unsigned short *) (function +74))
#define tramp_variable(function)  \
  hilo(*(unsigned short *) (function + 2), \
       *(unsigned short *) (function + 6), \
       *(unsigned short *) (function +14), \
       *(unsigned short *) (function +22))
#define tramp_data(function)  \
  hilo(*(unsigned short *) (function +26), \
       *(unsigned short *) (function +30), \
       *(unsigned short *) (function +38), \
       *(unsigned short *) (function +46))
#endif
#ifdef __mips64__
  /* function:
   *    ld $2,24($25)			DF 22 00 18
   *    ld $3,32($25)			DF 23 00 20
   *    sd $3,0($2)			FC 43 00 00
   *    ld $25,40($25)			DF 39 00 28
   *    j $25				03 20 00 08
   *    nop				00 00 00 00
   *    .dword <variable>		<variable>
   *    .dword <data>			<data>
   *    .dword <address>		<address>
   */
  *(long *)          (function + 0) = 0xDF220018DF230020L;
  *(long *)          (function + 8) = 0xFC430000DF390028L;
  *(long *)          (function +16) = 0x0320000800000000L;
  *(unsigned long *) (function +24) = (unsigned long) variable;
  *(unsigned long *) (function +32) = (unsigned long) data;
  *(unsigned long *) (function +40) = (unsigned long) address;
#define TRAMP_CODE_LENGTH  24
#define is_tramp(function)  \
  *(long *)          (function + 0) == 0xDF220018DF230020L && \
  *(long *)          (function + 8) == 0xFC430000DF390028L && \
  *(long *)          (function +16) == 0x0320000800000000L
#define tramp_address(function)  \
  *(unsigned long *) (function +40)
#define tramp_variable(function)  \
  *(unsigned long *) (function +24)
#define tramp_data(function)  \
  *(unsigned long *) (function +32)
#endif
#if defined(__sparc__) && !defined(__sparc64__)
  /* function:
   *    sethi %hi(<variable>),%g1	03000000 | (<variable> >> 10)
   *    sethi %hi(<data>),%g2		05000000 | (<data> >> 10)
   *    or %g2,%lo(<data>),%g2		8410A000 | (<data> & 0x3ff)
   *    st %g2,[%g1+%lo(<variable>)]	C4206000 | (<variable> & 0x3ff)
   *    sethi %hi(<address>),%g1	03000000 | (<address> >> 10)
   *    jmp %g1+%lo(<address>)		81C06000 | (<address> & 0x3ff)
   *    nop				01000000
   */
#define hi(word)  ((unsigned long) (word) >> 10)
#define lo(word)  ((unsigned long) (word) & 0x3ff)
  *(long *) (function + 0) = 0x03000000 | hi(variable);
  *(long *) (function + 4) = 0x05000000 | hi(data);
  *(long *) (function + 8) = 0x8410A000 | lo(data);
  *(long *) (function +12) = 0xC4206000 | lo(variable);
  *(long *) (function +16) = 0x03000000 | hi(address);
  *(long *) (function +20) = 0x81C06000 | lo(address);
  *(long *) (function +24) = 0x01000000;
#define is_tramp(function)  \
  (*(long *) (function + 0) & 0xffc00000) == 0x03000000 && \
  (*(long *) (function + 4) & 0xffc00000) == 0x05000000 && \
  (*(long *) (function + 8) & 0xfffffc00) == 0x8410A000 && \
  (*(long *) (function +12) & 0xfffffc00) == 0xC4206000 && \
  (*(long *) (function +16) & 0xffc00000) == 0x03000000 && \
  (*(long *) (function +20) & 0xfffffc00) == 0x81C06000 && \
   *(long *) (function +24)               == 0x01000000
#define hilo(hiword,loword)  (((hiword) << 10) | ((loword) & 0x3ff))
#define tramp_address(function)  \
  hilo(*(long *) (function +16), *(long *) (function +20))
#define tramp_variable(function)  \
  hilo(*(long *) (function + 0), *(long *) (function +12))
#define tramp_data(function)  \
  hilo(*(long *) (function + 4), *(long *) (function + 8))
#endif
#ifdef __sparc64__
  /* function:
   *    rd %pc,%g1			83414000
   *    ldx [%g1+24],%g2		C4586018
   *    ldx [%g1+32],%g3		C6586020
   *    ldx [%g1+40],%g1		C2586028
   *    jmp %g1				81C04000
   *    stx %g3,[%g2]			C6708000
   *    .long high32(<variable>)	<variable> >> 32
   *    .long low32(<variable>)		<variable> & 0xffffffff
   *    .long high32(<data>)		<data> >> 32
   *    .long low32(<data>)		<data> & 0xffffffff
   *    .long high32(<address>)		<address> >> 32
   *    .long low32(<address>)		<address> & 0xffffffff
   */
  *(int *)  (function + 0) = 0x83414000;
  *(int *)  (function + 4) = 0xC4586018;
  *(int *)  (function + 8) = 0xC6586020;
  *(int *)  (function +12) = 0xC2586028;
  *(int *)  (function +16) = 0x81C04000;
  *(int *)  (function +20) = 0xC6708000;
  *(long *) (function +24) = (long) variable;
  *(long *) (function +32) = (long) data;
  *(long *) (function +40) = (long) address;
#define TRAMP_CODE_LENGTH  24
#define is_tramp(function)  \
  *(int *)  (function + 0) == 0x83414000 && \
  *(int *)  (function + 4) == 0xC4586018 && \
  *(int *)  (function + 8) == 0xC6586020 && \
  *(int *)  (function +12) == 0xC2586028 && \
  *(int *)  (function +16) == 0x81C04000 && \
  *(int *)  (function +20) == 0xC6708000
#define tramp_address(function)  \
  *(long *) (function +40)
#define tramp_variable(function)  \
  *(long *) (function +24)
#define tramp_data(function)  \
  *(long *) (function +32)
#endif
#ifdef __alpha__
  /* function:
   *    br $1,function..ng	00 00 20 C0
   * function..ng:
   *    ldq $2,20($1)		14 00 41 A4
   *    ldq $3,28($1)		1C 00 61 A4
   *    ldq $27,36($1)		24 00 61 A7
   *    stq $2,0($3)		00 00 43 B4
   *    jmp $31,($27),0		00 00 FB 6B
   *    .quad <data>		<data>
   *    .quad <variable>	<variable>
   *    .quad <address>		<address>
   */
  { static int code [6] =
      { 0xC0200000, 0xA4410014, 0xA461001C, 0xA7610024, 0xB4430000, 0x6BFB0000 };
    int i;
    for (i=0; i<6; i++) { ((int *) function)[i] = code[i]; }
    ((long *) function)[3] = (long) data;
    ((long *) function)[4] = (long) variable;
    ((long *) function)[5] = (long) address;
  }
#define TRAMP_CODE_LENGTH  24
#define is_tramp(function)  \
  ((int *) function)[0] == 0xC0200000 && \
  ((int *) function)[1] == 0xA4410014 && \
  ((int *) function)[2] == 0xA461001C && \
  ((int *) function)[3] == 0xA7610024 && \
  ((int *) function)[4] == 0xB4430000 && \
  ((int *) function)[5] == 0x6BFB0000
#define tramp_address(function)  \
  ((long *) function)[5]
#define tramp_variable(function)  \
  ((long *) function)[4]
#define tramp_data(function)  \
  ((long *) function)[3]
#endif
#ifdef __hppaold__
  /* function:
   *    ldil L'<data>,%r20		22800000 | hi(<data>)
   *    ldil L'<variable>,%r19		22600000 | hi(<variable>)
   *    ldo R'<data>(%r20),%r20		36940000 | lo(<data>)
   *    stw %r20,R'<variable>(%r19)	6A740000 | lo(<variable>)
   *    ldil L'<address>,%r21		22A00000 | hi(<address>)
   *    ldo R'<address>(%r21),%r21	36B50000 | lo(<address>)
   *    bb,>=,n %r21,30,function2	C7D5C012
   *    depi 0,31,2,%r21		D6A01C1E
   *    ldw 4(0,%r21),%r19		4AB30008
   *    ldw 0(0,%r21),%r21		4AB50000
   * function2:
   *    ldsid (0,%r21),%r1		02A010A1
   *    mtsp %r1,%sr0			00011820
   *    be,n 0(%sr0,%r21)		E2A00002
   *    nop				08000240
   */
  /* When decoding a 21-bit argument in an instruction, the hppa performs
   * the following bit manipulation:
   * assemble21: x[20]...x[0]
   *       --> x[0] x[11]...x[1] x[15]..x[14] x[20]...x[16] x[13]..x[12]
   * When encoding a 21-bit argument into an instruction, we need the
   * to perform the reverse permutation:
   * permute21:  y[20]...y[0]
   *       --> y[6]...y[2] y[8]..y[7] y[1]..y[0] y[19]...y[9] y[20]
   */
#define assemble21(x)  \
  ((((x) & 0x1) << 20) | (((x) & 0xFFE) << 8) | \
   (((x) & 0xC000) >> 7) | (((x) & 0x1F0000) >> 14) | (((x) & 0x3000) >> 12))
#define permute21(y)  \
  ((((y) & 0x7C) << 14) | (((y) & 0x180) << 7) | (((y) & 0x3) << 12) | \
   (((y) & 0xFFE00) >> 8) | (((y) & 0x100000) >> 20))
#define hi(word)  permute21((unsigned long) (word) >> 11)
#define lo(word)  (((unsigned long) (word) & 0x7FF) << 1)
  *(long *) (function + 0) = 0x22800000 | hi(data);
  *(long *) (function + 4) = 0x22600000 | hi(variable);
  *(long *) (function + 8) = 0x36940000 | lo(data);
  *(long *) (function +12) = 0x6A740000 | lo(variable);
  *(long *) (function +16) = 0x22A00000 | hi(address);
  *(long *) (function +20) = 0x36B50000 | lo(address);
  *(long *) (function +24) = 0xC7D5C012;
  *(long *) (function +28) = 0xD6A01C1E;
  *(long *) (function +32) = 0x4AB30008;
  *(long *) (function +36) = 0x4AB50000;
  *(long *) (function +40) = 0x02A010A1;
  *(long *) (function +44) = 0x00011820;
  *(long *) (function +48) = 0xE2A00002;
  *(long *) (function +52) = 0x08000240;
#define is_tramp(function)  \
  ((long) function & 3) == 0 && \
  (*(long *) (function + 0) & 0xffe00000) == 0x22800000 && \
  (*(long *) (function + 4) & 0xffe00000) == 0x22600000 && \
  (*(long *) (function + 8) & 0xfffff000) == 0x36940000 && \
  (*(long *) (function +12) & 0xfffff000) == 0x6A740000 && \
  (*(long *) (function +16) & 0xffe00000) == 0x22A00000 && \
  (*(long *) (function +20) & 0xfffff000) == 0x36B50000 && \
  *(long *) (function +24) == 0xC7D5C012 && \
  *(long *) (function +28) == 0xD6A01C1E && \
  *(long *) (function +32) == 0x4AB30008 && \
  *(long *) (function +36) == 0x4AB50000 && \
  *(long *) (function +40) == 0x02A010A1 && \
  *(long *) (function +44) == 0x00011820 && \
  *(long *) (function +48) == 0xE2A00002 && \
  *(long *) (function +52) == 0x08000240
#define hilo(hiword,loword)  \
  ((assemble21((unsigned long) (hiword)) << 11) | \
   (((unsigned long) (loword) & 0xFFE) >> 1) \
  )
#define tramp_address(function)  \
  hilo(*(long *) (function +16), *(long *) (function +20))
#define tramp_variable(function)  \
  hilo(*(long *) (function + 4), *(long *) (function +12))
#define tramp_data(function)  \
  hilo(*(long *) (function + 0), *(long *) (function + 8))
#endif
#ifdef __hppanew__
  /* function:
   *    .long   tramp
   *    .long   closure
   * closure:
   *    .long   <variable>
   *    .long   <data>
   *    .long   <address>
   */
  { /* work around a bug in gcc 3.* */
    void* tramp_address = &tramp;
    *(long *) (function + 0) = ((long *) ((char*)tramp_address-2))[0];
    *(long *) (function + 4) = (long) (function + 8);
    *(long *) (function + 8) = (long) variable;
    *(long *) (function +12) = (long) data;
    *(long *) (function +16) = (long) address;
  }
#define TRAMP_CODE_LENGTH  0
#define is_tramp(function)  \
  ((long *) function)[0] == ((long *) ((char*)tramp_address-2))[0]
#define tramp_address(function)  \
  ((long *) function)[4]
#define tramp_variable(function)  \
  ((long *) function)[2]
#define tramp_data(function)  \
  ((long *) function)[3]
#endif
#ifdef __hppa64old__
  /* function:
   *    mfia %r27			000014BB
   *    ldd 40(%r27),%r31		537F0050
   *    ldd 48(%r27),%r1		53610060
   *    std %r1,0(%r31)			0FE112C0
   *    ldd 56(%r27),%r27		537B0070
   *    ldd 16(%r27),%r1		53610020
   *    ldd 24(%r27),%r27		537B0030
   *    bve (%r1)			E820D000
   *     nop				08000240
   *    .align 8
   *    .dword <variable>
   *    .dword <data>
   *    .dword <address>
   * function_pointer:
   *    .dword 0
   *    .dword 0
   *    .dword function
   *    .dword 0
   */
  *(int *)  (function + 0) = 0x000014BB;
  *(int *)  (function + 4) = 0x537F0050;
  *(int *)  (function + 8) = 0x53610060;
  *(int *)  (function +12) = 0x0FE112C0;
  *(int *)  (function +16) = 0x537B0070;
  *(int *)  (function +20) = 0x53610020;
  *(int *)  (function +24) = 0x537B0030;
  *(int *)  (function +28) = 0xE820D000;
  *(int *)  (function +32) = 0x08000240;
  *(long *) (function +40) = (long)variable;
  *(long *) (function +48) = (long)data;
  *(long *) (function +56) = (long)address;
  *(long *) (function +64) = (long)0;
  *(long *) (function +72) = (long)0;
  *(long *) (function +80) = (long)function;
  *(long *) (function +88) = (long)0;
#define TRAMP_CODE_LENGTH  36
#define is_tramp(function)  \
  *(int *) (function + 0) == 0x000014BB && \
  *(int *) (function + 4) == 0x537F0050 && \
  *(int *) (function + 8) == 0x53610060 && \
  *(int *) (function +12) == 0x0FE112C0 && \
  *(int *) (function +16) == 0x537B0070 && \
  *(int *) (function +20) == 0x53610020 && \
  *(int *) (function +24) == 0x537B0030 && \
  *(int *) (function +28) == 0xE820D000 && \
  *(int *) (function +32) == 0x08000240
#define tramp_address(function)  \
  (*(unsigned long *) (function +56))
#define tramp_variable(function)  \
  (*(unsigned long *) (function +40))
#define tramp_data(function)  \
  (*(unsigned long *) (function +48))
#endif
#ifdef __hppa64new__
  /* function:
   *    .dword 0
   *    .dword 0
   *    .dword tramp
   *    .dword closure
   * closure:
   *    .dword <variable>
   *    .dword <data>
   *    .dword <address>
   */
  *(long *) (function + 0) = 0;
  *(long *) (function + 8) = 0;
  *(long *) (function +16) = ((long *) (void*) &tramp)[2];
  *(long *) (function +24) = (long) (function + 32);
  *(long *) (function +32) = (long) variable;
  *(long *) (function +40) = (long) data;
  *(long *) (function +48) = (long) address;
#define TRAMP_CODE_LENGTH  0
#define is_tramp(function)  \
  ((long *) function)[2] == ((long *) (void*) &tramp)[2] && \
  ((long *) function)[3] == (long) (function + 32)
#define tramp_address(function)  \
  ((long *) function)[6]
#define tramp_variable(function)  \
  ((long *) function)[4]
#define tramp_data(function)  \
  ((long *) function)[5]
#endif
#if defined(__arm__) || defined(__armhf__)
  /* function:
   *	stmfd	sp!,{r0}		E92D0001
   * 	ldr	r0,[pc,#16]		E59F000C
   *	ldr	ip,[pc,#16]		E59FC00C
   *	str	r0,[ip]			E58C0000
   *	ldmfd	sp!,{r0}		E8BD0001
   *	ldr	pc,[pc,#4]		E59FF004
   * _data:
   *	.word	<data>
   * _variable:
   *	.word	<variable>
   * _address:
   *	.word	<address>
   */
  {
    ((long *) function)[0] = 0xE92D0001;
    ((long *) function)[1] = 0xE59F000C;
    ((long *) function)[2] = 0xE59FC00C;
    ((long *) function)[3] = 0xE58C0000;
    ((long *) function)[4] = 0xE8BD0001;
    ((long *) function)[5] = 0xE59FF004;
    ((long *) function)[6] = (long)data;
    ((long *) function)[7] = (long)variable;
    ((long *) function)[8] = (long)address;
  }
#define TRAMP_CODE_LENGTH  24
#define is_tramp(function)  \
    ((long *) function)[0] == 0xE92D0001 && \
    ((long *) function)[1] == 0xE59F000C && \
    ((long *) function)[2] == 0xE59FC00C && \
    ((long *) function)[3] == 0xE58C0000 && \
    ((long *) function)[4] == 0xE8BD0001 && \
    ((long *) function)[5] == 0xE59FF004
#define tramp_address(function)  \
  ((long *) function)[8]
#define tramp_variable(function)  \
  ((long *) function)[7]
#define tramp_data(function)  \
  ((long *) function)[6]
#endif
#ifdef __arm64__
  /* function:
   *    ldr x9,.+24		580000C9
   *    ldr x10,.+28		580000EA
   *    ldr x11,.+32		5800010B
   *    str x9,[x10]		F9000149
   *    br x11			D61F0160
   *    nop			D503201F
   *    .xword <data>		<data>
   *    .xword <variable>	<variable>
   *    .xword <address>	<address>
   */
  *(int *)   (function + 0) = 0x580000C9;
  *(int *)   (function + 4) = 0x580000EA;
  *(int *)   (function + 8) = 0x5800010B;
  *(int *)   (function +12) = 0xF9000149;
  *(int *)   (function +16) = 0xD61F0160;
  *(int *)   (function +20) = 0xD503201F;
  *(long *)  (function +24) = (unsigned long) data;
  *(long *)  (function +32) = (unsigned long) variable;
  *(long *)  (function +40) = (unsigned long) address;
#define TRAMP_CODE_LENGTH  24
#define is_tramp(function)  \
  *(unsigned int *) (function + 0) == 0x580000C9 && \
  *(unsigned int *) (function + 4) == 0x580000EA && \
  *(unsigned int *) (function + 8) == 0x5800010B && \
  *(unsigned int *) (function +12) == 0xF9000149 && \
  *(unsigned int *) (function +16) == 0xD61F0160 && \
  *(unsigned int *) (function +20) == 0xD503201F
#define tramp_address(function)  \
  (*(unsigned long *) (function +40))
#define tramp_variable(function)  \
  (*(unsigned long *) (function +32))
#define tramp_data(function)  \
  (*(unsigned long *) (function +24))
#endif
#ifdef __powerpcsysv4__
  /* function:
   *    {liu|lis} 11,hi16(<variable>)		3D 60 hi16(<variable>)
   *    {oril|ori} 11,11,lo16(<variable>)	61 6B lo16(<variable>)
   *    {liu|lis} 12,hi16(<data>)		3D 80 hi16(<data>)
   *    {oril|ori} 12,12,lo16(<data>)		61 8C lo16(<data>)
   *    {st|stw} 12,0(11)			91 8B 00 00
   *    {liu|lis} 0,hi16(<address>)		3C 00 hi16(<address>)
   *    {oril|ori} 0,0,lo16(<address>)		60 00 lo16(<address>)
   *    mtctr 0					7C 09 03 A6
   *    bctr					4E 80 04 20
   */
  *(short *) (function + 0) = 0x3D60;
  *(short *) (function + 2) = (unsigned long) variable >> 16;
  *(short *) (function + 4) = 0x616B;
  *(short *) (function + 6) = (unsigned long) variable & 0xffff;
  *(short *) (function + 8) = 0x3D80;
  *(short *) (function +10) = (unsigned long) data >> 16;
  *(short *) (function +12) = 0x618C;
  *(short *) (function +14) = (unsigned long) data & 0xffff;
  *(long *)  (function +16) = 0x918B0000;
  *(short *) (function +20) = 0x3C00;
  *(short *) (function +22) = (unsigned long) address >> 16;
  *(short *) (function +24) = 0x6000;
  *(short *) (function +26) = (unsigned long) address & 0xffff;
  *(long *)  (function +28) = 0x7C0903A6;
  *(long *)  (function +32) = 0x4E800420;
#define is_tramp(function)  \
  *(unsigned short *) (function + 0) == 0x3D60 && \
  *(unsigned short *) (function + 4) == 0x616B && \
  *(unsigned short *) (function + 8) == 0x3D80 && \
  *(unsigned short *) (function +12) == 0x618C && \
  *(unsigned long *)  (function +16) == 0x918B0000 && \
  *(unsigned short *) (function +20) == 0x3C00 && \
  *(unsigned short *) (function +24) == 0x6000 && \
  *(unsigned long *)  (function +28) == 0x7C0903A6 && \
  *(unsigned long *)  (function +32) == 0x4E800420
#define hilo(hiword,loword)  \
  (((unsigned long) (hiword) << 16) | (unsigned long) (loword))
#define tramp_address(function)  \
  hilo(*(unsigned short *) (function +22), *(unsigned short *) (function +26))
#define tramp_variable(function)  \
  hilo(*(unsigned short *) (function + 2), *(unsigned short *) (function + 6))
#define tramp_data(function)  \
  hilo(*(unsigned short *) (function +10), *(unsigned short *) (function +14))
#endif
#ifdef __powerpcaix__
  /* function:
   *    .long .tramp
   *    .long .mytoc
   *    .long 0
   * .mytoc:
   *    .long <variable>
   *    .long <data>
   *    .long <address>
   */
  *(long *)  (function + 0) = ((long *) &tramp)[0];
  *(long *)  (function + 4) = (long) (function + 12);
  *(long *)  (function + 8) = 0;
  *(long *)  (function +12) = (long) variable;
  *(long *)  (function +16) = (long) data;
  *(long *)  (function +20) = (long) address;
#define TRAMP_CODE_LENGTH  0
#define is_tramp(function)  \
  ((long *) function)[0] == ((long *) &tramp)[0]
#define tramp_address(function)  \
  ((long *) function)[5]
#define tramp_variable(function)  \
  ((long *) function)[3]
#define tramp_data(function)  \
  ((long *) function)[4]
#endif
#ifdef __powerpc64_elfv2__
  /* function:
   *    ld 11,24(12)		18 00 6C E9
   *    ld 0,32(12)		20 00 0C E8
   *    std 0,0(11)		00 00 0B F8
   *    ld 12,40(12)		28 00 8C E9
   *    mtctr 12		A6 03 89 7D
   *    bctr			20 04 80 4E
   *    .quad <variable>
   *    .quad <data>
   *    .quad <address>
   */
  *(int *)   (function + 0) = 0xE96C0018;
  *(int *)   (function + 4) = 0xE80C0020;
  *(int *)   (function + 8) = 0xF80B0000;
  *(int *)   (function +12) = 0xE98C0028;
  *(int *)   (function +16) = 0x7D8903A6;
  *(int *)   (function +20) = 0x4E800420;
  *(long *)  (function +24) = (unsigned long) variable;
  *(long *)  (function +32) = (unsigned long) data;
  *(long *)  (function +40) = (unsigned long) address;
#define TRAMP_CODE_LENGTH  24
#define is_tramp(function)  \
  *(unsigned int *) (function + 0) == 0xE96C0018 && \
  *(unsigned int *) (function + 4) == 0xE80C0020 && \
  *(unsigned int *) (function + 8) == 0xF80B0000 && \
  *(unsigned int *) (function +12) == 0xE98C0028 && \
  *(unsigned int *) (function +16) == 0x7D8903A6 && \
  *(unsigned int *) (function +20) == 0x4E800420
#define tramp_address(function)  \
  (*(unsigned long *) (function +40))
#define tramp_variable(function)  \
  (*(unsigned long *) (function +24))
#define tramp_data(function)  \
  (*(unsigned long *) (function +32))
#endif
#ifdef __powerpc64aix__
  /* function:
   *    .quad .tramp
   *    .quad .mytoc
   *    .quad 0
   * .mytoc:
   *    .quad <variable>
   *    .quad <data>
   *    .quad <address>
   */
  *(long *)  (function + 0) = ((long *) &tramp)[0];
  *(long *)  (function + 8) = (long) (function + 24);
  *(long *)  (function +16) = 0;
  *(long *)  (function +24) = (long) variable;
  *(long *)  (function +32) = (long) data;
  *(long *)  (function +40) = (long) address;
#define TRAMP_CODE_LENGTH  0
#define is_tramp(function)  \
  ((long *) function)[0] == ((long *) &tramp)[0]
#define tramp_address(function)  \
  ((long *) function)[5]
#define tramp_variable(function)  \
  ((long *) function)[3]
#define tramp_data(function)  \
  ((long *) function)[4]
#endif
#ifdef __ia64__
  /* function:
   *    data8   tramp
   *    data8   closure
   * closure:
   *    data8   <address>
   *    data8   <variable>
   *    data8   <data>
   */
  *(long *) (function + 0) = (long) &tramp;
  *(long *) (function + 8) = (long) (function + 16);
  *(long *) (function +16) = (long) address;
  *(long *) (function +24) = (long) variable;
  *(long *) (function +32) = (long) data;
#define TRAMP_CODE_LENGTH  0
#define is_tramp(function)  \
  ((long *) function)[0] == (long) &tramp
#define tramp_address(function)  \
  ((long *) function)[2]
#define tramp_variable(function)  \
  ((long *) function)[3]
#define tramp_data(function)  \
  ((long *) function)[4]
#endif
#ifdef __x86_64__
#ifdef __x86_64_x32__
  /* function:
   *    movl $<data>,<variable>		C7 04 25 <variable> <data>
   *    movl $<address>,%eax		B8 <address>
   *    jmp *%rax			FF E0
   */
  *(int *)   (function + 0) = ((unsigned long) variable << 24) | 0x2504C7;
  *(int *)   (function + 4) = ((unsigned long) data << 24) | ((unsigned long) variable >> 8);
  *(int *)   (function + 8) = 0xB8000000 | ((unsigned long) data >> 8);
  *(int *)   (function +12) = (unsigned long) address;
  *(short *) (function +16) = 0xE0FF;
#define is_tramp(function)  \
  (*(unsigned long *) (function + 0) & 0x00FFFFFF) == 0x2504C7 && \
  (*(unsigned long *) (function + 8) & 0xFF000000) == 0xB8000000 && \
  *(unsigned short *) (function +16) == 0xE0FF
#define tramp_address(function)  \
  (*(unsigned int *) (function +12))
#define tramp_variable(function)  \
  ((*(unsigned long *) (function + 0) >> 24) | \
   (*(unsigned long *) (function + 4) << 8))
#define tramp_data(function)  \
  ((*(unsigned long *) (function + 4) >> 24) | \
   (*(unsigned long *) (function + 8) << 8))
#else
  /* function:
   *    movabsq $<data>,%rax		48 B8 <data>
   *    movabsq %rax, <variable>	48 A3 <variable>
   *    movabsq $<address>,%rax		48 B8 <address>
   *    jmp *%rax			FF E0
   */
  *(short *) (function + 0) = 0xB848;
  *(short *) (function + 2) = (unsigned long long) data & 0xffff;
  *(int *)   (function + 4) = ((unsigned long long) data >> 16) & 0xffffffff;
  *(short *) (function + 8) = ((unsigned long long) data >> 48) & 0xffff;
  *(short *) (function +10) = 0xA348;
  *(int *)   (function +12) = (unsigned long long) variable & 0xffffffff;
  *(int *)   (function +16) = ((unsigned long long) variable >> 32) & 0xffffffff;
  *(short *) (function +20) = 0xB848;
  *(short *) (function +22) = (unsigned long long) address & 0xffff;
  *(int *)   (function +24) = ((unsigned long long) address >> 16) & 0xffffffff;
  *(short *) (function +28) = ((unsigned long long) address >> 48) & 0xffff;
  *(short *) (function +30) = 0xE0FF;
#define is_tramp(function)  \
  *(unsigned short *) (function + 0) == 0xB848 && \
  *(unsigned short *) (function +10) == 0xA348 && \
  *(unsigned short *) (function +20) == 0xB848 && \
  *(unsigned short *) (function +30) == 0xE0FF
#define hilo(hiword,loword)  \
  (((unsigned long long) (hiword) << 32) | (unsigned long long) (loword))
#define himidlo(hishort,midword,loshort)  \
  (((unsigned long long) (hishort) << 48) | (unsigned long long) (midword) << 16 \
   | (unsigned long long) (loshort))
#define tramp_address(function)  \
  himidlo(*(unsigned short *) (function +28), \
          *(unsigned int *)   (function +24), \
          *(unsigned short *) (function +22))
#define tramp_variable(function)  \
  hilo(*(unsigned int *) (function +16), *(unsigned int *) (function +12))
#define tramp_data(function)  \
  himidlo(*(unsigned short *) (function + 8), \
          *(unsigned int *)   (function + 4), \
          *(unsigned short *) (function + 2))
#endif
#endif
#if defined(__s390__) && !defined(__s390x__)
  /* function:
   *    bras %r1,.L1			A7150002
   * .L1:
   *    l %r0,data-.L1(%r1)		58001018
   *    l %r1,variable-.L1(%r1)		5810101C
   *    st %r0,0(%r1)			50001000
   *    bras %r1,.L2			A7150002
   * .L2:
   *    l %r1,function-.L2(%r1)		58101010
   *    br %r1				07F1
   *    nop				0707
   * data:     .long <data>
   * variable: .long <variable>
   * address:  .long <address>
   */
  *(int *)   (function + 0) = 0xA7150002;
  *(int *)   (function + 4) = 0x58001018;
  *(int *)   (function + 8) = 0x5810101C;
  *(int *)   (function +12) = 0x50001000;
  *(int *)   (function +16) = 0xA7150002;
  *(int *)   (function +20) = 0x58101010;
  *(int *)   (function +24) = 0x07F10707;
  *(int *)   (function +28) = (unsigned int) data;
  *(int *)   (function +32) = (unsigned int) variable;
  *(int *)   (function +36) = (unsigned int) address;
#define TRAMP_CODE_LENGTH  28
#define is_tramp(function)  \
  *(unsigned int *) (function + 0) == 0xA7150002 && \
  *(unsigned int *) (function + 4) == 0x58001018 && \
  *(unsigned int *) (function + 8) == 0x5810101C && \
  *(unsigned int *) (function +12) == 0x50001000 && \
  *(unsigned int *) (function +16) == 0xA7150002 && \
  *(unsigned int *) (function +20) == 0x58101010 && \
  *(unsigned int *) (function +24) == 0x07F10707
#define tramp_address(function)  \
  *(unsigned int *) (function +36)
#define tramp_variable(function)  \
  *(unsigned int *) (function +32)
#define tramp_data(function)  \
  *(unsigned int *) (function +28)
#endif
#ifdef __s390x__
  /* function:
   *    larl %r1,.L1			C01000000003
   * .L1:
   *    lg %r0,data-.L1(%r1)		E30010220004
   *    lg %r1,variable-.L1(%r1)	E310102A0004
   *    stg %r0,0(%r1)			E30010000024
   *    larl %r1,.L2			C01000000003
   * .L2:
   *    lg %r1,function-.L2(%r1)	E310101A0004
   *    br %r1				07F1
   *    nop				0707
   * data:     .quad <data>
   * variable: .quad <variable>
   * address:  .quad <address>
   */
  *(int *)   (function + 0) = 0xC0100000;
  *(int *)   (function + 4) = 0x0003E300;
  *(int *)   (function + 8) = 0x10220004;
  *(int *)   (function +12) = 0xE310102A;
  *(int *)   (function +16) = 0x0004E300;
  *(int *)   (function +20) = 0x10000024;
  *(int *)   (function +24) = 0xC0100000;
  *(int *)   (function +28) = 0x0003E310;
  *(int *)   (function +32) = 0x101A0004;
  *(int *)   (function +36) = 0x07F10707;
  *(long *)  (function +40) = (unsigned long) data;
  *(long *)  (function +48) = (unsigned long) variable;
  *(long *)  (function +56) = (unsigned long) address;
#define TRAMP_CODE_LENGTH  40
#define is_tramp(function)  \
  *(unsigned int *) (function + 0) == 0xC0100000 && \
  *(unsigned int *) (function + 4) == 0x0003E300 && \
  *(unsigned int *) (function + 8) == 0x10220004 && \
  *(unsigned int *) (function +12) == 0xE310102A && \
  *(unsigned int *) (function +16) == 0x0004E300 && \
  *(unsigned int *) (function +20) == 0x10000024 && \
  *(unsigned int *) (function +24) == 0xC0100000 && \
  *(unsigned int *) (function +28) == 0x0003E310 && \
  *(unsigned int *) (function +32) == 0x101A0004 && \
  *(unsigned int *) (function +36) == 0x07F10707
#define tramp_address(function)  \
  (*(unsigned long *) (function +56))
#define tramp_variable(function)  \
  (*(unsigned long *) (function +48))
#define tramp_data(function)  \
  (*(unsigned long *) (function +40))
#endif

  /* 3. Set memory protection to "executable" */

#if !defined(CODE_EXECUTABLE)
#if defined(EXECUTABLE_VIA_MALLOC_THEN_MPROTECT) || defined(EXECUTABLE_VIA_MMAP_THEN_MPROTECT)
  /* Call mprotect on the pages that contain the range. */
  { uintptr_t start_addr = (uintptr_t) function;
    uintptr_t end_addr = (uintptr_t) (function + TRAMP_LENGTH);
    start_addr = start_addr & -pagesize;
    end_addr = (end_addr + pagesize-1) & -pagesize;
   {uintptr_t len = end_addr - start_addr;
#if defined(HAVE_MACH_VM)
    if (vm_protect(task_self(),start_addr,len,0,VM_PROT_READ|VM_PROT_WRITE|VM_PROT_EXECUTE) != KERN_SUCCESS)
#else
    if (mprotect((void*)start_addr, len, PROT_READ|PROT_WRITE|PROT_EXEC) < 0)
#endif
      { fprintf(stderr,"trampoline: cannot make memory executable\n"); abort(); }
  }}
#endif
#endif

  /* 4. Flush instruction cache */
  /* We need this because some CPUs have separate data cache and instruction
   * cache. The freshly built trampoline is visible to the data cache, but not
   * maybe not to the instruction cache. This is hairy.
   */
  /* TRAMP_CODE_LENGTH = length of the machine instructions. */
#ifndef TRAMP_CODE_LENGTH
#define TRAMP_CODE_LENGTH TRAMP_LENGTH
#endif
#if !(defined(__hppanew__) || defined(__hppa64new__) || defined(__powerpcaix__) || defined(__powerpc64aix__) || defined(__ia64__))
  /* Only needed if we really set up machine instructions. */
#ifdef __i386__
#if defined(_WIN32)
  while (!FlushInstructionCache(GetCurrentProcess(),function_x,TRAMP_CODE_LENGTH))
    continue;
#endif
#endif
#ifdef __m68k__
#if defined(__NetBSD__) && defined(__GNUC__)
  { register uintptr_t _beg __asm__ ("%a1") = (uintptr_t) function_x;
    register uintptr_t _len __asm__ ("%d1") = TRAMP_CODE_LENGTH;
    __asm__ __volatile__ (
      "move%.l %#0x80000004,%/d0\n\t" /* CC_EXTPURGE | C_IPURGE */
      "trap #12"                      /* kernel call ‘cachectl’ */
      :
      : "a" (_beg), "d" (_len)
      : "%a0", "%a1", "%d0", "%d1"    /* call-used registers */
      );
  }
#endif
#if defined(__linux__) && defined(__GNUC__)
  { register uintptr_t _beg __asm__ ("%d1") = (uintptr_t) function_x;
    register uintptr_t _len __asm__ ("%d4") = TRAMP_CODE_LENGTH + 32;
    __asm__ __volatile__ (
      "move%.l %#123,%/d0\n\t"
      "move%.l %#1,%/d2\n\t"
      "move%.l %#3,%/d3\n\t"
      "trap %#0"
      :
      : "d" (_beg), "d" (_len)
      : "%d0", "%d2", "%d3"
      );
  }
#endif
#if defined(AUX) && defined(__GNUC__)
  /* sysm68k(105, addr, scope, cache, len) */
  __asm__ __volatile__ (
    "move%.l %1,%/sp@-\n\t"
    "move%.l %#3,%/sp@-\n\t"
    "move%.l %#1,%/sp@-\n\t"
    "move%.l %0,%/sp@-\n\t"
    "move%.l %#105,%/sp@-\n\t"
    "move%.l %#0,%/sp@-\n\t"
    "move%.l %#38,%/sp@-\n\t"
    "trap %#0\n\t"
    "add%.l %#24,%/sp"
    :
    : "r" (function_x), "g" ((int)TRAMP_CODE_LENGTH)
    : "%d0"
    );
#endif
#endif
#if defined(__mips__) || defined(__mipsn32__) || defined(__mips64__)
  cacheflush(function_x,TRAMP_CODE_LENGTH,ICACHE);
  /* gforth-0.3.0 uses BCACHE instead of ICACHE. Why?? */
#endif
#if defined(__sparc__) || defined(__sparc64__)
  /* This assumes that the trampoline fits in at most four cache lines. */
  __TR_clear_cache_4(function_x,function_x+TRAMP_CODE_LENGTH-1);
#endif
#ifdef __alpha__
  __TR_clear_cache();
#endif
#if defined(__hppa__) || defined(__hppa64__)
  /* This assumes that the trampoline fits in at most two cache lines. */
  __TR_clear_cache(function_x,function_x+TRAMP_CODE_LENGTH-1);
#endif
#if defined(__arm__) || defined(__armhf__) || defined(__arm64__)
  /* On ARM, cache flushing can only be done through a system call.
     GCC implements it for Linux with EABI, through an "swi 0" with code
     0xf0002. For other systems, it may be an "swi 0x9f0002",
     an "swi 0xf00000", or similar.  */
  /* On ARM64, cache flushing is done through special instructions,
     and the length of the cache lines must be determined at runtime.
     See gcc/libgcc/config/aarch64/sync-cache.c. */
#if defined(__GNUC__)
  /* Use the GCC built-in. */
  __clear_cache((void*)function_x,(void*)(function_x+TRAMP_CODE_LENGTH));
#else
  #error "Don't know how to implement clear_cache on this platform."
#endif
#endif
#if defined(__powerpc__) || defined(__powerpc64__)
  __TR_clear_cache(function_x);
#endif
#endif

  /* 5. Return. */
  return (trampoline_function_t) (function_x + TRAMP_BIAS);
}

void free_trampoline (trampoline_function_t function)
{
#if TRAMP_BIAS
  function = (trampoline_function_t)((char*)function - TRAMP_BIAS);
#endif
#if !defined(CODE_EXECUTABLE) && !defined(EXECUTABLE_VIA_MALLOC_THEN_MPROTECT)
#ifdef EXECUTABLE_VIA_MMAP_FILE_SHARED
  /* Find the writable address corresponding to the executable address. */
  { uintptr_t page_x = (uintptr_t) function & -(intptr_t)pagesize;
    function -= ((intptr_t*)page_x)[0];
  }
#endif
  *(char**)function = freelist; freelist = (char*)function;
  /* It is probably not worth calling munmap() for entirely freed pages. */
#else
  free(((char**)function)[-1]);
#endif
}

int is_trampoline (void* function)
{
#ifdef is_tramp
#ifdef __hppanew__
  void* tramp_address = &tramp;
  if (!(((uintptr_t)function & 3) == (TRAMP_BIAS & 3))) return 0;
#endif
  return ((is_tramp(((char*)function - TRAMP_BIAS))) ? 1 : 0);
#else
  abort();
#endif
}

trampoline_function_t trampoline_address (trampoline_function_t function)
{
#ifdef tramp_address
  return (trampoline_function_t)(tramp_address(((char*)function - TRAMP_BIAS)));
#else
  abort();
#endif
}

void** trampoline_variable (trampoline_function_t function)
{
#ifdef tramp_variable
  return (void**)(tramp_variable(((char*)function - TRAMP_BIAS)));
#else
  abort();
#endif
}

void* trampoline_data (trampoline_function_t function)
{
#ifdef tramp_data
  return (void*)(tramp_data(((char*)function - TRAMP_BIAS)));
#else
  abort();
#endif
}
