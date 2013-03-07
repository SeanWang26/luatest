#include <stdio.h>
#include <string.h>
#include<stdlib.h>

#include <lua.h>
#include <lauxlib.h>



extern int luaopen_seanlab(lua_State *L);

static void stackDump (lua_State *L) {
  int i;
  int top = lua_gettop(L);

  printf("top is %d\n", top);
  
  for (i = 1; i <= top; i++) {	/* repeat for each level */
	int t = lua_type(L, i);
	switch (t) {

	  case LUA_TSTRING:  /* strings */
		printf("`%s'", lua_tostring(L, i));
		break;

	  case LUA_TBOOLEAN:  /* booleans */
		printf(lua_toboolean(L, i) ? "true" : "false");
		break;

	  case LUA_TNUMBER:  /* numbers */
		printf("%g", lua_tonumber(L, i));
		break;

	  default:	/* other values */
		printf("%s", lua_typename(L, t));
		break;

	}
	printf("  ");  /* put a separator */
  }
  printf("\n");  /* end the listing */
}

/* call a function `f' defined in Lua */
double sinfun (lua_State *L, double x, double y) {
  double z;

  /* push functions and arguments */
  lua_getglobal(L, "sinfun");  /* function to be called */
  lua_pushnumber(L, x);   /* push 1st argument */
  lua_pushnumber(L, y);   /* push 2nd argument */

  /* do the call (2 arguments, 1 result) */
  if (lua_pcall(L, 2, 1, 0) != 0)
	error(L, "error running function `f': %s",
			 lua_tostring(L, -1));

  /* retrieve result */
  if (!lua_isnumber(L, -1))
	error(L, "function `f' must return a number");
  z = lua_tonumber(L, -1);
  lua_pop(L, 1);  /* pop returned value */
  return z;
}

int main(int argv, char **argc)
{
	printf("LUATEST build time %s\n", __TIME__);

	char buff[256];
	int error;

	int *t = NULL;
	t = (int*)malloc(0);
	printf("t=%p\n", t);
	free(t);
	
#if 0	
	//lua_State *L = luaL_newstate();
	lua_State *L = lua_open();   /* opens Lua */
	if(L==NULL)
	{
		printf("luaL_newstate error\n");
	}

	//WARNING: this code is for Lua 5.0. To run it in Lua 5.1, you must change the five calls luaopen_*(L) to a single call to luaL_openlibs(L)
	//luaopen_base(L);             /* opens the basic library */
	//luaopen_table(L);            /* opens the table library */
	//luaopen_io(L);               /* opens the I/O library */
	//luaopen_string(L);           /* opens the string lib. */
	//luaopen_math(L);             /* opens the math lib. */	
	luaL_openlibs(L);

	//while (fgets(buff, sizeof(buff), stdin) != NULL) {
	error = luaL_loadbuffer(L, buff, strlen(buff), "line") ||
		  lua_pcall(L, 0, 0, 0);
	if (error) {
		printf("error value:%d\n", error);
		fprintf(stderr, "Sean:%s\n", lua_tostring(L, -1));
		lua_pop(L, 1);	/* pop error message from the stack */
	}
	//}

	//24.2.1 ¨C Pushing Elements
    lua_pushnil (L);
    lua_pushboolean (L, 1);
    lua_pushnumber (L, 32.2);
	const char* str1 = "string 1";
    lua_pushlstring (L, str1, strlen(str1));
    lua_pushstring (L, "short string");

	//24.2.2 ¨C Querying Elements
    /*
	int intvalue = lua_toboolean (L, int index);
	double   doublevalue = lua_tonumber (L, int index);
	const char *strvalue = lua_tostring (L, int index);
	size_t strlen = lua_strlen (L, int index);
	*/

	stackDump(L);
	
	/*if (luaL_loadfile(L, "./lab.lua") || lua_pcall(L, 0, 0, 0))
	{
		//error(L, "cannot run configuration file: %s",
		//		 lua_tostring(L, -1));	

		printf("error value:%d\n", error);
		fprintf(stderr, "Sean:%s\n", lua_tostring(L, -1));
		lua_pop(L, 1);	// pop error message from the stack 

	}*/

	//printf("sinfun = %f\n", sinfun(L, 1, 2));

	//error = luaopen_lab(L);

	//stackDump(L);
	
	lua_close(L);

#endif
	printf("test2----------------------------------------------\n");

	int ji=0;
	int n = __sync_fetch_and_add(&ji, 1);
	printf("ji=%d, n=%d\n", ji, n);
	n = __sync_fetch_and_add(&ji, 2);
	printf("ji=%d, n=%d\n", ji, n);

	n = __sync_fetch_and_sub(&ji, 1);
	printf("ji=%d, n=%d\n", ji, n);
	n = __sync_fetch_and_sub(&ji, 2);
	printf("ji=%d, n=%d\n", ji, n);

	n = __sync_add_and_fetch(&ji, 1);
	printf("ji=%d, n=%d\n", ji, n);
	n = __sync_add_and_fetch(&ji, 2);
	printf("ji=%d, n=%d\n", ji, n);

	n = __sync_sub_and_fetch(&ji, 1);
	printf("ji=%d, n=%d\n", ji, n);
	n = __sync_sub_and_fetch(&ji, 2);
	printf("ji=%d, n=%d\n", ji, n);


#if 0
	printf("test3----------------------------------------------\n");
	//setenv("LUA_PATH","./?.lua",1);
	//setenv("LUA_CPATH","./?.so",1);

	lua_State *L = luaL_newstate();
	luaL_openlibs(L);
	int r = luaL_loadfile(L, "./lab.lua");

	r = lua_pcall(L,0,0,0);
	if(r){
		fprintf(stderr, "Sean:%s\n", lua_tostring(L, -1));
		lua_pop(L, 1);	// pop error message from the stack 
	}

	

	printf("r=%d\n", r);
	lua_close(L);
#endif

	printf("test4----------------------------------------------\n");
	lua_State *L  = luaL_newstate();
	luaL_openlibs(L);
	error = luaopen_seanlab(L);

	stackDump(L);

	int r = luaL_loadfile(L, "./printtable.lua");
	r = lua_pcall(L,0,0,0);

	stackDump(L);

	lua_close(L);

	return 0;
}
































