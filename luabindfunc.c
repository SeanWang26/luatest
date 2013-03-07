#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>


#include <stdio.h>


static int _functest(lua_State *L)
{

	printf("functest\n");
	
	int top = lua_gettop(L);
	
	printf("top=%d\n", top);

	luaL_checktype(L, 1, LUA_TNUMBER);
	luaL_checktype(L, 2, LUA_TNUMBER);
	luaL_checktype(L, 3, LUA_TNUMBER);

	/*luaL_checktype(L, 1, LUA_TSTRING);

	const char * cmd = luaL_checkstring(L,1);

	printf("[arg1]%s\n", cmd);

	const char * arint = luaL_checkstring(L,2);

	printf("[arg2]%s\n", arint);*/

	int darint1 = luaL_checkint(L,1);
	int darint2 = luaL_checkint(L,2);
	int darint3 = luaL_checkint(L,3);

	printf("[arg1]%d\n", darint1);
	printf("[arg2]%d\n", darint2);
	printf("[arg3]%d\n", darint3);

	lua_pushstring(L, "what in fun\n");

	return 1;
}

int luaopen_seanlab(lua_State *L)
{
	printf("[luaopen_lab]enter--------\n");

	luaL_Reg reg[] = {
					{"_functest" , _functest},
					{NULL, NULL},
					};
	
	//luaL_checkversion(L);

	lua_register(L, "stable", reg);

	/*luaL_newlibtable(L,reg);
	
	luaL_setfuncs(L,reg,0);
	lua_setglobal(L, reg);*/

	//luaL_register(L,"labtest",reg);

	printf("[luaopen_lab]leave-------\n");

	return 1;
}
































