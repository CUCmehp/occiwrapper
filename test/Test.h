#pragma once

//#define TEST( TestClass, TestFunctionName )	\
//	void TestClass#TestFunctionName()	\
//

#include <time.h>

bool operator == ( const struct tm& obj1, const struct tm& obj2 )
{
	return obj1.tm_year == obj2.tm_year && obj1.tm_mon == obj2.tm_mon && obj1.tm_mday == obj2.tm_mday &&
		   obj1.tm_hour == obj2.tm_hour && obj1.tm_min == obj2.tm_min && obj1.tm_sec == obj2.tm_sec;
}