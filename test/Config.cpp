#include "Config.h"
#include <iostream>
#include <iterator>
#include <sstream>

#ifdef WIN32
#include <windows.h>
#endif


common::Config::Config( string cfg_file )
{
	this->config_file_name = cfg_file;
	string file_path;
	if( common::CommFunc::check_file_exist( config_file_name ) )
	{
		file_path = config_file_name;
	}
	else
	{
#ifdef WIN32
		char buf[MAX_PATH];
		GetModuleFileName( NULL, buf, MAX_PATH );
		string path( buf );
		int pos = path.find_last_of("\\");
		string temp("\\");
		temp += config_file_name;
		path.replace( path.find_last_of( "\\" ), path.size(), temp );
		file_path = path;
#endif // WIN32
	}

	locale loc = locale::global( locale("") );
	ifstream fin( file_path.c_str() );
	locale::global( loc );
	if( !fin )
	{
		config_valid = false;
		return;
	}
	while( !fin.eof() )
	{
		char buf[1024] = { 0,0 };
		fin.getline( buf, 1024, '\n' );
		string str( buf );
		//Ìø¹ý¿ÕÐÐ
		if( str.size() == 0 )
			continue;
		//Ìø¹ý×¢ÊÍ
		if( str[0] == '#' )
			continue;
		stringstream ss;
		ss << str;
		vector< string > v_item;
		copy( istream_iterator< string >( ss ), istream_iterator< string >(), back_inserter( v_item ) );
		if( v_item.size() < 2 )
		{
			continue;
		}
		else
		{
			this->key_values.push_back( make_pair( v_item[0], v_item[1] ) );
		}

	}
	config_valid = true;
}

const string common::Config::getProperty( const string& key )
{
	for( size_t i = 0; i < this->key_values.size(); ++i )
	{
		string _key = key_values[i].first;
		if( _key == key )
		{
			return key_values[i].second;
		}
	}
	return "";
}

bool common::Config::valid()
{
	return this->config_valid;
}