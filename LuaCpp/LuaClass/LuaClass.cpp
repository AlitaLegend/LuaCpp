#include "LuaClass.h"

LuaClass::LuaClass():LuaState(NULL)
{ 
}

LuaClass::~LuaClass()
{
	if (LuaState)
	{
		lua_close(LuaState);
	}
}

//初始化Lua环境
bool LuaClass::CreateLuaState()
{
	LuaState = luaL_newstate();
	if (LuaState == NULL)
	{
		printf("LuaClass@CreateLuaState Fail!...\n");
		return false;
	}
	luaL_openlibs(LuaState);
	return true;

}

void LuaClass::PrintStackSize(char* Tag)
{
	if (!Tag)
	{
		cout << lua_gettop(LuaState) << endl;
	}
	else
	{
		cout << Tag <<":" <<lua_gettop(LuaState) << endl;
	}
}

void LuaClass::PrintStack(char* Tag)
{
	int LuaStateSize = lua_gettop(LuaState);
	if (Tag)
	{ 
		cout <<"------------"<< Tag << "------------STT"<< endl;
	} 

	printf("L:0x%x\n", LuaState);
	printf("size:%d\n", LuaStateSize);
	for (int i = 1; i <= LuaStateSize; i++)
	{
		printf("[%d](%s):%s\n", i, luaL_typename(LuaState, i), luaL_tolstring(LuaState, i, NULL));
		lua_pop(LuaState, 1);
	}
	cout << "------------" << Tag << "------------END" << endl;
}

bool LuaClass::DoFile(char* FilePath)
{
	if (FilePath ==NULL)
	{
		return false;
	}
	if (luaL_dofile(LuaState, FilePath) != 0)
	{
		char* ErrorMsg = (char*)lua_tostring(LuaState, -1);
		cout << "LuaClass@:dofile Fail! ErrorMsg = "<< ErrorMsg << endl;
		lua_pop(LuaState, 1);
		return false;
	}
	return true;
}

bool LuaClass::DoString(char* LuaString)
{
	if (LuaString == NULL)
	{
		return false;
	}
	if (luaL_dostring(LuaState, LuaString) != 0)
	{
		char* ErrorMsg = (char*)lua_tostring(LuaState, -1);
		cout << "LuaClass@:dofile Fail! ErrorMsg = " << ErrorMsg << endl;
		lua_pop(LuaState, 1);
		return false;
	}
	return  true;
}


bool LuaClass::GetGlobal(char* FieldName)
{
	if (lua_getglobal(LuaState, FieldName) <= 0)
	{
		return false;
	}
	return true;
}

bool LuaClass::SetGlobal(char* FieldName)
{
	if (lua_gettop(LuaState) < 1)
	{
		return false;
	}
	lua_setglobal(LuaState, FieldName);
	return true;
}
