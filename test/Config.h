#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <sstream>

using namespace std;

#pragma warning( disable : 4800 )

namespace common
{
	/**
	* @brief 本类用来封装一些通用的方法
	*/
	class CommFunc
	{
	public:
		/**
		* brief check a file existed or not
		*/
		static bool check_file_exist( const string& file_path, bool is_dir = false )
		{
			struct stat info;
			if( stat( file_path.c_str(), &info ) != 0 )
			{
				return false;
			}
			if( !is_dir )
			{
				return (bool)(S_IFREG & info.st_mode); 
			}
			else
			{
				return (bool)(S_IFDIR & info.st_mode);
			}
		}
	};

	/**
	* @brief 用来解析配置文件，支持ini文件
	*/
	class Config
	{
	public:
		Config( string cfg_file );

		const string getProperty( const string& key );

		template< typename T >
		bool getProperty(const string& key, T& value )
		{
			string str = getProperty( key );
			try
			{
				if( !str.empty() )
				{
					stringstream ss;
					ss << str;
					ss >> value;			
					return true;
				}
			}
			catch( ... )
			{
				return false;
			}
			return false;
		}

		bool valid();
	private:
		bool config_valid;

		string config_file_name;

		vector< pair< string, string> > key_values;
	};
}

