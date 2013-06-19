mudos+dtxy的安装

修改options
cp options.h local_options
#define NO_WIZARDS 修改为 #undef NO_WIZARDS
#undef PACKAGE_UIDS 修改为 #define PACKAGE_UIDS
#define SENSIBLE_MODIFIERS 修改为 #undef SENSIBLE_MODIFIERS

mudos安装
./build.MudOS ‘develop’：develop模式编译打开gcc –g -DDEBUG -DDEBUG_MACRO选项，方便gdb调试。
gmake clean
gmake, 错误及解决
gmake: *** No rule to make target `obj/malloc.o', needed by `driver'.  Stop.
这个错误不管它，继续执行一次gmake就可以通过。
socket_efuns.c: In function 'get_socket_addres':
socket_efuns.c:1198: error: invalid lvalue in unary '&'
gmake: *** [obj/socket_efuns.o] Error 1
Doing this change fixes the issue: 
 就是把取地址的&符号移到?运算里面去，继续gmake就可以了。
再gmake，然后gmake install就行了

mud启动参数
–D 预定义
–N no_ip_demon 不需要启动address_server
–y  打开yydebug
–m 指定mudlib目录
–f  是否调用master::flag函数
–e  是否加载preload文件
–p 监听端口
–d 调试级别
–c是否输出编译信息
–t t_flag++ 是否调用call_heart_beat
dtxy启动调试

添加static目录.  

执行时段错误：*Wrong permissions for opening file /log/static/CRASHES for append.
将i < size 改成 i < sizeof(buf1)
Miscd.c 39行，报2nd argument to < is not numeric when the 1st is.

#define CFG_MAX_LOCAL_VARIABLES  25  修改为 100
执行时段错误：*Error in loading object '/adm/daemons/combatd'
Log文件报/adm/daemons/combatd.c line 1343: Too many local variables before the end of line
/d/obj/misc/jitan.h中将#define SHILI_D "/adm/daemons/shili" 定义提前
将几个.c文件中的include移动到inherit前面
新建topten目录，*Wrong permissions for opening file /data/topten/rich.o for overwrite.  "No such file or directory"

mudos启动流程分析
set_defaults(rc.c) ：解析配置文件，设置系统变量
init_addr_server ：初始化address server 
init_simul_efun和init_master()：装载mudlib的simul_efun和master
preload_objects ：预加载对象
调用master的APPLY_EPILOG函数，返回文件列表
调用master的APPLY_PRELOAD函数，加载对象

backend(backend.c)
init_user_conn 初始化用户连接, 设置非阻塞模式并监听. 
循环调用select函数获取读写时间
process_io(comm.c) 处理io内容
new_user_handler：如果external_port有可读内容，处理新用户连接
 /adm/object/master.connect()  /obj/login.logon()  /adm/daemon/logind.logon()
用户连接中的socket如果有可读数据，get_user_data
读取socket数据，放入buf中
cmd_in_buf，清理缓存，如果buf包含分行符，设置有cmd的标记位
用户连接中的socket如果有可写数据，flush_message
处理efun_socket上的socket数据
处理address server的数据
process_user_command (comm..c) 处理用户命令
get_user_command 获取用户命令
call_function_interactive 执行命令
