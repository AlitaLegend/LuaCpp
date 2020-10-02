#include "TestLuaClass.h"

TestLuaClass::TestLuaClass()
{
}


TestLuaClass::~TestLuaClass()
{
}

void TestLuaClass::Test()
{
	if (CreateLuaState())
	{
		if (!DoFile(_strdup("./ex5.lua")))
		{
			return;
		}
		
		if (GetGlobal(_strdup("Test1")))
		{
			LuaPush<char*>(_strdup("A"));
			LuaPush<char*>(_strdup("b"));
			PrintStack(_strdup("GetGlobal"));
			if (lua_pcall(GetLuaState(), 2,-1, 0)!=0)
			{
				lua_pop(GetLuaState(), 1);//µ¯³ö´íÎóÖµ
				PrintStack(_strdup("lua_pcall erro"));
				return;
			}
			PrintStack(_strdup("lua_pcall end"));
			cout << LuaGet<int>(1) << "," <<LuaGet<int>(2) << "," << LuaGet<char*>(3) << endl;
			lua_pop(GetLuaState(),3);
			PrintStack(_strdup("end"));
		}
	}
}