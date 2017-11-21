#include <stdio.h>
#include "lua.h"
#include "lauxlib.h"
#include <pthread.h>



void* new_thread(void* data)
{


     
   lua_State* L = luaL_newstate();

   luaL_openlibs(L);

   luaL_dofile(L, "demo.lua");

   while(1)
        {
                lua_getglobal(L, "demo");
                lua_pcall(L, 0,0,0);
                sleep(1);
        }


    return NULL;
}

int main()
{
   printf("sdfdsf");

   pthread_t id;


   pthread_create(&id, NULL, new_thread, NULL);

   
	
   lua_State* L = luaL_newstate();
		
   luaL_openlibs(L);	
 	
   luaL_dofile(L, "demo.lua");


   

   while(1)
   	{
   		lua_getglobal(L, "demo");
		lua_pcall(L, 0,0,0);
		sleep(1);
 	}

   return 0;
}
