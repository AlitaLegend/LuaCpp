#pragma once
#include <iostream>
#include "lua.hpp"

using namespace std;
class LuaClass
{
public:
	//初始化Lua环境
	bool CreateLuaState();
	void PrintStackSize(char* tag = NULL);
	void PrintStack(char* tag = NULL);
	bool dofile(char* f);
	bool dostring(char* f);
	bool GetGlobal(char* name);
	bool SetGlobal(char* name);

	inline lua_State* GetLuaState()
	{
		return m_lua;
	}
	
	LuaClass();
	~LuaClass();




	///////////////////////////////特化Get///////////////////////////////////////////
	template<typename _Ty>
	_Ty LuaGet(int index = -1);	
	template<> inline	char* LuaGet<char*>(int index)
	{	 
		if (!LuaCheck<char*>(index))
		{
			cout << "erro check!" << endl;
		}
		return (char*)lua_tostring(m_lua, index);
	}	
	template<> string LuaGet<string>(int index)
	{
		if (!LuaCheck<char*>(index))
		{
			cout << "erro check!" << endl;
		}

		string tmpstr = (char*)lua_tostring(m_lua, index);
		return std::move(tmpstr);
	}
	template<> inline int LuaGet<int>(int index /* = -1 */)
	{

		if (!LuaCheck<int>(index))
		{
			cout << "erro check!" << endl;
		}

		return lua_tonumber(m_lua, index);
	}
	template<> inline double LuaGet<double>(int index /* = -1 */)
	{

		if (!LuaCheck<double>(index))
		{
			cout << "erro check!" << endl;
		}

		return lua_tonumber(m_lua, index);
	}

	///////////////////////////////特化Check///////////////////////////////////////////
	template<typename _Ty>
	bool LuaCheck(int index = -1);
	template<>	bool LuaCheck<char*>(int index)//检查是否是字符串
	{
		return lua_isstring(m_lua, index) == 0 ? false : true;
	}

	template<>	bool LuaCheck<string>(int index)
	{
		return lua_isstring(m_lua, index) == 0 ? false : true;
	}

	template<>	bool LuaCheck<int>(int index)
	{
		return lua_isnumber(m_lua, index) == 0 ? false : true;
	}

	template<>	bool LuaCheck<double>(int index)
	{
		return lua_isnumber(m_lua, index) == 0 ? false : true;
	}

	//////////////////////////////////特化Push////////////////////////////////////////
	template<typename _TY>
	void LuaPush(_TY);
	template<> void LuaPush<char*>(char* t)
	{
		lua_pushstring(m_lua, t);
	}

	template<> void LuaPush<int>(int t)
	{
		lua_pushnumber(m_lua, t);
	}

	template<> void LuaPush<double>(double t)
	{
		lua_pushnumber(m_lua, t);
	}

	//////////////////////////////特化 获取全局变量////////////////////////////////////////////
	template<typename _Ty>
	_Ty LuaGetGlobal(char*global, bool _pop = true);
	template<>	char* LuaGetGlobal<char*>(char*global, bool _pop)
	{
		if (GetGlobal(global) == false)
		{
			cout << "erro check!" << endl;
		} 
		char* tmp = LuaGet<char*>();
		//char* tmp = (char*)lua_tostring(m_lua, -1);
		if (_pop)
		{ 
			lua_pop(m_lua, 1); 
		} 
		 
	     return tmp;
	 
	
	}
	template<> string LuaGetGlobal<string>(char*global, bool _pop)
	{
		if (GetGlobal(global) == false)
		{
			cout << "erro check!" << endl;
		} 
		//string tmpstr = (char*)lua_tostring(m_lua, -1);
		string tmpstr = LuaGet<char*>();
		if (_pop)
		{ 
			lua_pop(m_lua, 1); 
		} 
		return std::move(tmpstr);
	}
	template<> int LuaGetGlobal<int>(char*global, bool _pop)
	{
		if (GetGlobal(global) == false)
		{
			cout << "erro check!" << endl;
		} 
		int tmp = LuaGet<int>();
		//int tmp  = lua_tonumber(m_lua, -1);
		if (_pop)
		{
			lua_pop(m_lua, 1);
		}
		return tmp;
	}
	template<> double LuaGetGlobal<double>(char*global, bool _pop)
	{
		if (GetGlobal(global) == false)
		{
			cout << "erro check!" << endl;
		} 
		double tmp = LuaGet<double>();
		//double tmp = lua_tonumber(m_lua, -1);
		if (_pop)
		{
			lua_pop(m_lua, 1);
		}
		return tmp;
	}

	//////////////////////////////特化 设置全局变量////////////////////////////////////////////
	template<typename _Ty>
	bool LuaSetGlobal(_Ty data, char*global);
	template<>	bool LuaSetGlobal<char*>(char*data, char*global)
	{
		lua_pushstring(m_lua, data);
		if (SetGlobal(global) == false)
		{
			cout << "erro check!" << endl;
			return false;
		}
		return true;
	} 
	template<>	bool LuaSetGlobal<int>(int data, char*global)
	{
		lua_pushnumber(m_lua, data);
		if (SetGlobal(global) == false)
		{
			cout << "erro check!" << endl;
			return false;
		}
		return true;
	}

	template<>	bool LuaSetGlobal<double>(double data, char*global)
	{
		lua_pushnumber(m_lua, data);
		if (SetGlobal(global) == false)
		{
			cout << "erro check!" << endl;
			return false;
		}
		return true;
	}

	template<>	bool LuaSetGlobal<string>(string data, char*global)
	{
		lua_pushstring(m_lua, data.c_str());
		if (SetGlobal(global) == false)
		{
			cout << "erro check!" << endl;
			return false;
		}
		return true;
	}
	 

	
private:
	lua_State* m_lua;
};

