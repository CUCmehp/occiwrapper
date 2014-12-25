occiwrapper
===========

Occiwrapper is an open source and cross platform Oracle Driver that delivers efficient access to Oracle database. It was written by C++, and offers a rich, full featured API. It helps C++ developers operate Oracle database easily. With Occiwrapper, you can execute SQL with following format:

开发occiwrapper这个库，主要是为了封装一个跨平台的OCCI的访问组件，方使C++开发者们灵活地操作oracle数据库。为了方便使用，组件中的接口形式参考的POCO库的使用方式。<br /><br />
使用如下的形式执行SQL语句：<br />

>        occiwrapper::Session s = SessionInstance( connection );
>        s << "truncate table TBL_TEST ", now;

The Oracle session is maintained by the Session object. The SQL is imported into the session and executed; this operation is analogous to the stream.
For parameter binding, with the help of Occiwrapper, you can directly bind the C++ variable to the Oracle parameter. For more information, please see details in the documentation afterwards.

通过session对象维护一个到oracle的会话。类似于流的操作方式，向session中传入SQL语句，并执行。<br />
在oracle参数绑定方面，可以直接将C++变量绑定给oracle参数中，在以后的文档说明中详细介绍。<br />

>        occiwrapper::Session s = SessionInstance( info );
>        struct tm tm_value; 
>        s << "insert into TBL_TEST( date_value ) values ( :1 )", use( tm_value ), now;

Meanwhile, you can directly bind a vector to the Oracle binding parameter and easily retrieve the result which is returned by select operation into a vector, and you do not need to care about the correspondence of the type. In order to improve the access performance, the batch mode is taken for writing and reading. The smart pointer is used to manage memory buffer pool automatically, which can set the Oracle developers free.

同时，对于vector等容量变量，可以灵活地直接绑定到oracle的绑定变量上，同时也可以灵活的将select语句返回的结果绑定到容器中，而且对于使用者来讲，并不用关心类型的对应关系。为了提高存取的性能，写入和读取都采入批量操作的方式，同时采用智能指针自动管理内存缓冲池，最大限度地解放了oracle开发者。<br />

>        occiwrapper::Session s = SessionInstance( info );
>        vector< int > vec1;
>        s << "select A from tbl_test2 t", into( vec1 ), now;

Most technics used in the component are from my experiences and summaries in daily work. Owing to the limitation of my Oracle and C++ knowledge, I hope we can discuss together, and I will revise the bugs you submit ASAP; your participation in revising the library is also highly appreciated.

组件中使用的很多技术都是在工作中一些经验的积累与总结，由于自己认识oracle不够深刻，对C++的理解也可能不够深入，希望大家多多讨论。对于大家发现的Bug，我也会尽快修改，同时热情欢迎大家积极参与库的修改。<br />

代码地址为:[https://github.com/CUCmehp/occiwrapper](https://github.com/CUCmehp/occiwrapper)

联系作者：CUCmehp@foxmail.com QQ交流群：348648166 <br />
Contact author: CUCmehp@foxmail.com QQ Group:348648166 <br />

编译说明
===========
Windows
-----------
**使用Visual Studio 2008 SP1工具**<br />
使用Visual Studio 2008直接打开工程occi\_wrapper\_vs2008.sln, 选择Debug和Release进行编译。<br />
注：要求vs2008 sp1以上，是由于occiwrapper中使用了tr1库，而vs2008从SP1版本以上，才开始支持tr1库。<br />


**使用Visual Studio 2010**<br />
使用Visual Studio 2010直接打开工程occi\_wrapper\_vs2010.sln, 选择Debug和Release进行编译。<br />
说明：源码中include/occi_11g目录下，存放着oracle 11.2.0.2 64位数据库对应的头文件，在lib\_vs2008和lib\_vs2010目录下，存放着11.2.0.2版数据库对应的lib库文件。在bin\_vs2008和bin\_vs2010目录下，存放着对应的dll文件。<br />
若需要使用其它版本的occi库版本，则将上述文件替换为需要使用的occi库文件。<br />
	
Linux
-----------
linux下使用，需要先下载oracle occi库对应的头文件和动态库文件。在oracle数据库的OCI/lib目录下，通常可以找到这些文件。若未安装oracle数据库，则可以从[官网](http://www.oracle.com/technetwork/topics/linuxx86-64soft-092277.html)上下载：<br />
头文件对应文件包为：instantclient-sdk-linux.x64-\*.\*.\*.\*.\*.zip <br />
库对应文件包为：instantclient-basic-linux.x64-\*.\*.\*.\*.\*.zip <br />
只需要选择需要的oracle版本，下载对就的文件就可以，然后解压，记得将so文件放在系统运行时扫描的目录，如/usr/local/lib、/usr/lib等目录，也可以将so的目录添加到/etc/ld.so.conf配置文件中。<br />


下载[occiwrapper.tar.gz](https://github.com/CUCmehp/occiwrapper/releases)包，并在linux下解压，执行以下命令：<br />
>        tar -zxvf occiwrapper.tar.gz


genConfigure.sh生成可执行的权限，使用以下命令：<br />
>        chmod +x genConfigure.sh


运行此命令，运行的格式如下：<br />
>        ./genConfigure.sh --occi-include=occi_include_path_value --occi-lib=occi_lib_path_value

其中occi\_include\_path\_value对应着occi头文件的目录，occi\_lib\_path\_value对应着occi库文件的目录，比如头文件放在/u01/install/oracle_client/instantclient\_12\_1/sdk/include/,库文件存放在/u01/install/oracle\_client/instantclient\_12\_1/,则执行的命令为：<br />
>        ./genConfigure.sh --occi-include=/u01/install/oracle_client/instantclient_12_1/sdk/include/ --occi-lib=/u01/install/oracle_client/instantclient_12_1/


成功执行后，目录下会生成configure文件，然后执行./configure，默认安装在/usr/local目录下，也可以自己指定安装的目录，执行：<br />
>        ./configure --prefix=/usr/local/occiwrapper


编译程序，执行make命令。<br />
>        make


最后进行安装，执行<br />
>        make install


执行成功后，在/usr/local/occiwrapper目录下，存放着生成的include和lib文件，测试文件存放在test目录下，test目录下的db\_config.ini为测试库对应的配置信息。要执行test程序，需先在oracle数据库中执行db文件夹下的脚本。<br />




				

