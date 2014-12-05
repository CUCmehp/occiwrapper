/**
* @brief 定位宽整数,从Poco中取出部分定义
*/

namespace occiwrapper
{
#if defined(WIN32) || defined(WIN64)
	//
	// Windows/Visual C++
	//
	typedef signed char            Int8;
	typedef unsigned char          UInt8;
	typedef signed short           Int16;
	typedef unsigned short         UInt16;
	typedef int					   Int32;
	typedef unsigned int           UInt32;
	typedef signed __int64         Int64;
	typedef unsigned __int64       UInt64;
#else
	//
	// Unix/GCC
	//
	typedef signed char            Int8;
	typedef unsigned char          UInt8;
	typedef signed short           Int16;
	typedef unsigned short         UInt16;
	typedef int					   Int32;
	typedef unsigned int           UInt32;
	typedef signed long            IntPtr;
	typedef signed long long	   Int64;
	typedef unsigned long long	   UInt64;
#endif
}
