#include <iostream>
#include "LuaCore/lua.hpp"
#include "LuaClass/LuaClass.h" 
#include "LuaClass/TestLuaClass.h"

template<typename ArgT>
ArgT GetArg();

template<> inline int GetArg<int>()
{
	return 8848;
}

template<> inline char* GetArg<char*>()
{
	return _strdup("Mount Everest");
}

inline void  OutPrint(int Arg)
{
	cout << "OutPrint@int:" << endl;
	cout << Arg << endl;
}

inline void  OutPrint(char* Arg)
{
	cout << "OutPrint@char*:" << endl;
	cout << Arg << endl;
}

inline void OutPrint()
{
	cout << "OutPrint@void:" << endl;
}

template<typename FirstArgT, typename... ArgsT>
inline void OutPrint(int& CallCount, FirstArgT Ft, ArgsT...Args)
{
	cout << "OutPrint@ ...Args" << endl;
	CallCount++;
	OutPrint(Ft);
	OutPrint(CallCount, Args...);
}

template<typename ReturnT, typename... ArgsT>
inline ReturnT TestDynamicArgs(ArgsT...Args)
{
	cout << "TestDynamicArgs@...Args" << endl;
	int CallCount = 0;
	OutPrint(CallCount, Args...);
	cout << "CallCount:" << CallCount << endl;
	return GetArg<ReturnT>();
}
int main()
{
	auto Result = TestDynamicArgs<char*>(1, 2, 3);
	cout << "Result:" << Result << endl;

	//Call_Print(1, 2,(char*)"3");
   /*mclass->LuaPush<double>(1.1324);
   mclass->LuaPush<char*>("hello");*/

	getchar();
	return 0;
}
