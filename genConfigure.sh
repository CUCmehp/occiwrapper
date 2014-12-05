#!/bin/sh
#define path variables
str_occi_lib_path="";
str_occi_include_path="";
#show the usage of the command
function show_help()
{
        echo "command format:"
        echo "    ./genConfigure.sh --occi-include=path_value --occi-lib=path_value"
        echo "    example:"
        echo "         ./genConfigure.sh --occi-include=/usr/local/occi/include --occi-lib=/usr/local/lib"
        echo "    ./genConfigure.sh -h for help"
}

#parse occi include or lib path from parameter
function parse_occi()
{
        tmp=$1
        key=$(echo $tmp | awk -F ' ' '{print $0}' | awk -F '=' '{print $1}')
        value=$(echo $tmp | awk -F ' ' '{print $0}' | awk -F '=' '{print $2}')
        if [ "$key" = "--occi-include" ]
        then
                str_occi_include_path=$value
        fi

        if [ "$key" = "--occi-lib" ]
        then
                str_occi_lib_path=$value
        fi
}

#edit file
function edit_makefile()
{
        #edit Makefile.am
        sed -i '/^$/d' Makefile.am
        sed -i '/INCLUDES/d' Makefile.am ; echo 'INCLUDES=-I$(top_srcdir) -I$(top_srcdir)/include' -I$str_occi_include_path >> Makefile.am
        #edit test/Makefile.am
        sed -i '/^$/d' test/Makefile.am
        sed -i '/INCLUDES/d' test/Makefile.am ; echo 'INCLUDES=-I$(top_srcdir) -I$(top_srcdir)/include' -I$str_occi_include_path >> test/Makefile.am
        sed -i '/test_LDFLAGS/d' test/Makefile.am ; echo "test_LDFLAGS=-L$str_occi_lib_path" >> test/Makefile.am
}

#if need help
if [ "$1" = "-h" -o "$1" = "--h" ]
then
        show_help;
        exit;
fi

#test command is right or not
if [ -z $1 -o -z $2 ]
then
        show_help;
        exit
else
        parse_occi $1
        parse_occi $2
        #show occi path
        echo "occi include path:" $str_occi_include_path
        echo "occi lib path:" $str_occi_lib_path
        edit_makefile
fi

echo -------------------clean file--------------
rm -f configure Makefile.in Makefile ltmain.sh config.guess config.sub install-sh aclocal.m4
rm -rf autom4te.cache
echo -------------------aclocl------------------
aclocal
echo -------------------libtoolize--------------
libtoolize
echo -------------------autoconf----------------
autoconf
echo -------------------automake----------------
automake --add-missing
