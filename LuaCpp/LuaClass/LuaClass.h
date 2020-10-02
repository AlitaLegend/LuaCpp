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
	bool DoFile(char* FilePath);
	bool DoString(char* LuaString);
	bool GetGlobal(char* FieldName);
	bool SetGlobal(char* FieldName);

	inline lua_State* GetLuaState()
	{
		return LuaState;
	}
	
	LuaClass();
	~LuaClass();

	///////////////////////////////特化Get///////////////////////////////
	template<typename ReturnT>
	ReturnT LuaGet(int Index = -1);	
	template<> inline char* LuaGet<char*>(int Index)
	{	 
		if (!LuaCheck<char*>(Index))
		{
			cout << "LuaGet@error check char!" << endl;
		}
		return (char*)lua_tostring(LuaState, Index);
	}	

	template<> string LuaGet<string>(int Index)
	{
		if (!LuaCheck<char*>(Index))
		{
			cout << "LuaGet@error check string!" << endl;
		}

		string tmpstr = (char*)lua_tostring(LuaState, Index);
		return std::move(tmpstr);
	}

	template<> inline int LuaGet<int>(int Index /* = -1 */)
	{

		if (!LuaCheck<int>(Index))
		{
			cout << "LuaGet@error get int!" << endl;
		}

		return lua_tonumber(LuaState, Index);
	}

	template<> inline double LuaGet<double>(int Index /* = -1 */)
	{

		if (!LuaCheck<double>(Index))
		{
			cout << "LuaGet@error get double!" << endl;
		}

		return lua_tonumber(LuaState, Index);
	}

	///////////////////////////////特化Check///////////////////////////////
	template<typename ReturnT>
	bool LuaCheck(int Index = -1);
	template<>	bool LuaCheck<char*>(int Index)//检查是否是字符串
	{
		return lua_isstring(LuaState, Index) == 0 ? false : true;
	}

	template<>	bool LuaCheck<string>(int Index)
	{
		return lua_isstring(LuaState, Index) == 0 ? false : true;
	}

	template<>	bool LuaCheck<int>(int Index)
	{
		return lua_isnumber(LuaState, Index) == 0 ? false : true;
	}

	template<>	bool LuaCheck<double>(int Index)
	{
		return lua_isnumber(LuaState, Index) == 0 ? false : true;
	}

	//////////////////////////////////特化Push//////////////////////////////////
	template<typename ArgT>
	void LuaPush(ArgT);
	template<> void LuaPush<char*>(char* t)
	{
		lua_pushstring(LuaState, t);
	}

	template<> void LuaPush<int>(int t)
	{
		lua_pushnumber(LuaState, t);
	}

	template<> void LuaPush<double>(double t)
	{
		lua_pushnumber(LuaState, t);
	}

	//////////////////////////////特化 获取全局变量//////////////////////////////
	template<typename ReturnT>
	ReturnT LuaGetGlobal(char* Global, bool IsPop = true);
	template<>	char* LuaGetGlobal<char*>(char* Global, bool IsPop)
	{
		if (GetGlobal(Global) == false)
		{
			cout << "LuaGetGlobal@error get char!" << endl;
		} 
		char* tmp = LuaGet<char*>();
		if (IsPop)
		{ 
			lua_pop(LuaState, 1); 
		} 
	    return tmp;
	}

	template<> string LuaGetGlobal<string>(char* Global, bool IsPop)
	{
		if (GetGlobal(Global) == false)
		{
			cout << "LuaGetGlobal@error get string!" << endl;
		} 
		string tmpstr = LuaGet<char*>();
		if (IsPop)
		{ 
			lua_pop(LuaState, 1); 
		} 
		return std::move(tmpstr);
	}

	template<> int LuaGetGlobal<int>(char* Global, bool IsPop)
	{
		if (GetGlobal(Global) == false)
		{
			cout << "LuaGetGlobal@error get >!" << endl;
		} 
		int tmp = LuaGet<int>();
		if (IsPop)
		{
			lua_pop(LuaState, 1);
		}
		return tmp;
	}

	template<> double LuaGetGlobal<double>(char* Global, bool IsPop)
	{
		if (GetGlobal(Global) == false)
		{
			cout << "LuaGetGlobal@error get double>!" << endl;
		} 
		double tmp = LuaGet<double>();
		if (IsPop)
		{
			lua_pop(LuaState, 1);
		}
		return tmp;
	}

	//////////////////////////////特化 设置全局变量//////////////////////////////
	template<typename ArgT>
	bool LuaSetGlobal(ArgT Data, char* Global);
	template<>	bool LuaSetGlobal<char*>(char*Data, char*Global)
	{
		lua_pushstring(LuaState, Data);
		if (SetGlobal(Global) == false)
		{
			cout << "LuaSetGlobal@error get char" << endl;
			return false;
		}
		return true;
	} 

	template<>	bool LuaSetGlobal<int>(int Data, char*Global)
	{
		lua_pushnumber(LuaState, Data);
		if (SetGlobal(Global) == false)
		{
			cout << "LuaSetGlobal@error get int!" << endl;
			return false;
		}
		return true;
	}

	template<>	bool LuaSetGlobal<double>(double Data, char*Global)
	{
		lua_pushnumber(LuaState, Data);
		if (SetGlobal(Global) == false)
		{
			cout << "LuaSetGlobal@error get double!" << endl;
			return false;
		}
		return true;
	}

	template<>	bool LuaSetGlobal<string>(string Data, char*Global)
	{
		lua_pushstring(LuaState, Data.c_str());
		if (SetGlobal(Global) == false)
		{
			cout << "LuaSetGlobal@error get string!" << endl;
			return false;
		}
		return true;
	}
	
private:
	lua_State* LuaState;
};

