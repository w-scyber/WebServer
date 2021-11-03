
WebServer
===============

这是一个轻量级的Web服务器，目前支持GET、HEAD方法处理静态资源。

* 使用 **线程池 + 非阻塞socket + epoll(ET和LT均实现) + 事件处理(Reactor和模拟Proactor均实现)** 的并发模型
* 使用**状态机**解析HTTP请求报文，支持解析**GET和POST**请求
* 添加定时器支持HTTP长连接，定时回调handler处理超时连接
* 访问服务器数据库实现web端用户**注册、登录**功能，可以请求服务器**图片和视频文件**

测试页面: [http://120.78.85.58:43211/](http://120.78.85.58/)

------------

* 服务器测试环境

  * CentOS版本7
  * MySQL版本5.7.29

* 浏览器测试环境

  * Windows、Linux均可
  * Chrome
  * 其他浏览器暂无测试

* 测试前确认已安装MySQL数据库

  ```C++
  // 建立yourdb库
  create database yourdb;
  
  // 创建user表
  USE yourdb;
  CREATE TABLE user(
      username char(50) NULL,
      passwd char(50) NULL
  )ENGINE=InnoDB;
  
  // 添加数据
  INSERT INTO user(username, passwd) VALUES('name', 'passwd');
  ```

* 修改main.cpp中的数据库初始化信息

  ```C++
  //数据库登录名,密码,库名
  string user = "root";
  string passwd = "root";
  string databasename = "yourdb";
  ```

* 编译

  ```C++
  make
  ```

* 启动server

  ```C++
  ./server
  ```

* 浏览器端

  ```C++
  ip:43211
  ```

个性化运行
------

```C++
./server [-p port]  [-m TRIGMode] [-s sql_num] [-t thread_num] [-a actor_model]
```

温馨提示:以上参数不是非必须，不用全部使用，根据个人情况搭配选用即可.

* -p，自定义端口号
  * 默认43211
* -m，listenfd和connfd的模式组合，默认使用LT + LT
  * 0，表示使用LT + LT
  * 1，表示使用LT + ET
    * 2，表示使用ET + LT
    * 3，表示使用ET + ET
* -s，数据库连接数量
  * 默认为8
* -t，线程数量
  * 默认为8
* -a，选择反应堆模型，默认Proactor
  * 0，Proactor模型
  * 1，Reactor模型

测试示例命令与含义

```C++
./server -p 9007 -m 0 -s 10 -t 10 -a 1
```

- [x] 端口9007
- [x] 使用LT + LT组合
- [x] 数据库连接池内有10条连接
- [x] 线程池内有10条线程
- [x] Reactor反应堆模型

## 页面预览

主页界面

![image-20211103142621717](https://github.com/w-scyber/WebServer/blob/main/root/md_picture/main.png)

访问界面

![image-20211103142804523](https://github.com/w-scyber/WebServer/blob/main/root/md_picture/choice.png)请求图片

![image-20211103142836335](https://github.com/w-scyber/WebServer/blob/main/root/md_picture/p.png)

## 压力测试

采用webbench对服务器进行压力测试，服务器采用ET + ET模式，并采用Reactor反应堆模型

测试所用的服务器为1核2G阿里云服务器，性能较差会对QPS以及成功请求数做出限制，但仍可以承受住上万请求的并发，并不会出现访问失败的请求

![image-20211103143619611](https://github.com/w-scyber/WebServer/blob/main/root/md_picture/web1.png)

![image-20211103143639593](https://github.com/w-scyber/WebServer/blob/main/root/md_picture/web2.png)

## 开发计划

+ 添加异步日志系统，记录服务器运行状态
+ 类似nginx的反向代理和负载均衡
+ 采用智能指针实现内存分配
