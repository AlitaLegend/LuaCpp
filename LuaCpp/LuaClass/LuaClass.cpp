#include "LuaClass.h"

LuaClass::LuaClass():m_lua(NULL)
{ 
}


LuaClass::~LuaClass()
{
	if (m_lua)
	{
		lua_close(m_lua);
	}
}


//��ʼ��Lua����
bool LuaClass::CreateLuaState()
{
	m_lua = luaL_newstate();
	if (m_lua == NULL)
	{
		printf("error Lua��ʼ������ʧ��!�����쳣...\n");
		return false;
	}
	luaL_openlibs(m_lua);
	return true;

}

void LuaClass::PrintStackSize(char* tag)
{
	 
	if (!tag)
	{
		cout << lua_gettop(m_lua) << endl;
	}
	else
	{
		cout << tag<<":" <<lua_gettop(m_lua) << endl;
	}

}


void LuaClass::PrintStack(char* tag)
{
	int size_ = lua_gettop(m_lua);

	
	if (tag)
	{ 
		cout <<"    ******"<<tag << "******"<< endl;
	} 
	printf("L:0x%x\n", m_lua);
	printf("size:%d\n",size_);
	for (int i = 1; i <= size_; i++)
	{
		printf("[%d](%s):%s\n", i, luaL_typename(m_lua, i),luaL_tolstring(m_lua,i,NULL));
		lua_pop(m_lua, 1);
	}
	printf("\n\n");

}

//#include <windows.h>
bool LuaClass::dofile(char* f)
{
	if (f==NULL)
	{
		return false;
	}
	if (luaL_dofile(m_lua, f)!=0)
	{
		char* errostr = (char*)lua_tostring(m_lua, -1);
		cout << "dofileʧ��:"<< errostr << endl;
		//::MessageBoxA(0, errostr, "dofileʧ��", 0);
		lua_pop(m_lua,1);
		return false;
	}

	return  true;
}



bool LuaClass::dostring(char* f)
{
	if (f == NULL)
	{
		return false;
	}
	if (luaL_dostring(m_lua, f) != 0)
	{
		char* errostr = (char*)lua_tostring(m_lua, -1);
		cout << "dostringʧ��:" << errostr << endl;
		//::MessageBoxA(0, errostr, "dofileʧ��", 0);
		lua_pop(m_lua, 1);
		return false;
	}

	return  true;
}


bool LuaClass::GetGlobal(char* name)
{
	if (lua_getglobal(m_lua, name)<=0)
	{
		return false;
	}
	return true;
}

bool LuaClass::SetGlobal(char* name)
{
	if (lua_gettop(m_lua)<1)
	{
		return false;
	}
	lua_setglobal(m_lua, name);
	return true;
}
