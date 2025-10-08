// 事件循环与事件处理
// 1.上节课介绍了事件循环的基本实现，但该事件循环不能增加socket监听IO事件，也没有处理IO事件。
// 2.本节课将使用event来处理IO事件，event是一个事件处理的抽象类。
// 事件与事件处理函数
// 1.事件是由文件描述符的就绪事件触发。
// 2.事件处理函数是回调函数，用于处理特定事件的发生。
// event类的定义
// 1.event类包含事件处理函数和文件描述符。
// 2.event通过文件描述符与事件循环绑定，以便在事件发生时找到正确的事件处理函数。
// event类的设计
// 1.event是一个抽象类，定义了关闭、出错、读、写等事件的接口。
// 2.事件处理函数在同一个事件循环中执行，保证线程安全。
// 3.VN成员变量包括文件描述符、事件循环指针和事件类型。
// event类的实现
// 1.定义了命名空间和成员函数，包括出错、读写、使能等函数。
// 2.成员变量包括文件描述符、事件循环指针和事件类型。
// 3.实现了析构函数，用于关闭文件句柄。
// 事件循环与事件的关联
// 1.在事件循环中增加成员变量和函数，用于保存和管理事件。
// 2.增加了增加事件、删除事件和使能函数的实现。
// 3.使用智能指针和哈希表来关联文件描述符和事件。
// 事件处理流程
// 1.在事件循环中判断事件的合法性，通过文件描述符查找事件。
// 2.找到事件后调用事件处理函数，处理出错情况。
// 3.使用局部变量确保事件循环指针的线程安全性。
#pragma once
#include <string>
#include <sys/epoll.h>
#include <memory>

namespace tmms
{
    namespace network
    {
        class EventLoop;
        const int kEventRead = (EPOLLIN | EPOLLPRI | EPOLLET);
        const int kEventWrite = (EPOLLOUT | EPOLLET);
        class Event:public std::enable_shared_from_this<Event>
        {
            friend class EventLoop;

        private:
            EventLoop *loop_{nullptr};
            int fd_{-1};
            int event_{0};

        public:
            Event();
            Event(EventLoop *loop, int fd);
            ~Event();

            virtual void OnRead() {};
            virtual void OnWrite() {};
            virtual void OnError(const std::string &err_msg) {};
            virtual void OnClose() {};
            bool EnableWriting(bool enable);
            bool EnableReading(bool enable);
            int Fd() const;
        };

    } // namespace network

} // namespace tmms
