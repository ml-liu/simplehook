
#include <stdio.h>
#include <dlfcn.h>
#include "funchook.h"
#include <stdlib.h>

typedef int (*hooktype)(int a, const char* b);


hooktype g_f = NULL;
int hookf(int a, const char*b){
    printf("in hookf b=%s\n", b);
    g_f(a, b);
    return 1;
}

int f(int a, const char*b){
    printf("in f b=%s\n", b);
    return 1;
}


typedef void*  (*malloc_type)(size_t);



malloc_type g_old_malloc = NULL;

void* malloc_hook1(size_t size)
{
   // printf("malloc_hook size=%lu\n", size);
    void* ret = g_old_malloc(size);
    printf("malloc_hook ret=%p\n", ret);

    return ret;

}

int main(int c, char**b)
{

    funchook_t *funchook = funchook_create();

    //g_f = f;
    g_old_malloc = malloc;

    void* handle = dlopen("/lib/libc-2.5.so", 1);

    g_old_malloc = dlsym(handle, "malloc");
    funchook_prepare(funchook, (void**)&g_old_malloc, malloc_hook1);

    funchook_install(funchook, 0);

    void* p =  malloc(199);


    printf("\np=%p\n", p);
    while(9){
    p = malloc(199);
    printf("\np=%p\n", p);
    sleep(5);
}
    //f(1, "bbbb");

    return 0;
}
