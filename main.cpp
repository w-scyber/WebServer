#include "webserver.h"

int main(int argc, char *argv[])
{
    //需要修改的数据库信息,登录名,密码,库名
    string user = "ws";
    string passwd = "ws150";
    string databasename = "yourdb";

    WebServer server;

    int PORT = 43211;  //默认端口号
    int TRIGMode = 0;  //触发组合模式,默认listenfd LT + connfd LT
    int LISTENTrigmode = 0;  //listenfd触发模式，默认LT
    int CONNTrigmode = 0;  //connfd触发模式，默认LT
    int sql_num = 8;  //默认数据库连接池数量
    int thread_num = 8;  //默认线程池内的线程数量
    int actor_model = 0;  //并发模型,默认是proactor

  
    int opt;
    const char *str = "p:l:m:s:t:c:a:";
    while ((opt = getopt(argc, argv, str)) != -1)
    {
        switch (opt)
        {
        case 'p':
        {
            PORT = atoi(optarg);
            break;
        }
        case 'm':
        {
            TRIGMode = atoi(optarg);
            break;
        }
        case 's':
        {
            sql_num = atoi(optarg);
            break;
        }
        case 't':
        {
            thread_num = atoi(optarg);
            break;
        }
        case 'a':
        {
            actor_model = atoi(optarg);
            break;
        }
        default:
            break;
        }
    }


    //初始化
    server.init(PORT, user, passwd, databasename,  TRIGMode,  sql_num,
		thread_num, actor_model);
    
    //数据库
    server.sql_pool();

    //线程池
    server.thread_pool();

    //触发模式
    server.trig_mode();

    //监听
    server.eventListen();

    //运行
    server.eventLoop();

    return 0;
}
