// #include <stdio.h>
// int main(int argc, const char **argv)
// {
//     printf("HelloWorld!\n");
//     return 0;
// }

// #include "../base/Singleton.h"
// #include <iostream>
// using namespace tmms::base;

// class A : public NonCopyable
// {
// private:
//     /* data */
// public:
//     A() = default;
//     ~A() = default;
//     void Print()
//     {
//         std::cout << "This is A!!!" << std::endl;
//     }
// };

// int main(int argc, const char **argv)
// {

//     auto sA = tmms::base::Singleton<A>::Instance();
//     sA->Print();
//     return 0;
// }

// #include "base/TaskMgr.h"
// #include "base/Task.h"
// #include "base/Singleton.h"
// #include "base/TTime.h"
// #include <iostream>
// #include <thread>
// #include <chrono>

// using namespace tmms::base;

// void TestTask()
// {
//     TaskPtr task1 = std::make_shared<Task>([](const TaskPtr &task)
//                                            { std::cout << "task1 intercal:" << 1000 << " now: " << TTime::NowMS() << std::endl; }, 1000);
//     TaskPtr task2 = std::make_shared<Task>([](const TaskPtr &task)
//                                            { std::cout << "task2 intercal:" << 1000<<" now: " <<TTime::NowMS() << std::endl;
//                                            task->Restart(); }, 1000);
//     TaskPtr task3 = std::make_shared<Task>([](const TaskPtr &task)
//                                            { std::cout << "task3 intercal:" << 500<<" now: " <<TTime::NowMS() << std::endl;
//                                            task->Restart(); }, 500);
//     TaskPtr task4 = std::make_shared<Task>([](const TaskPtr &task)
//                                            { std::cout << "task4 intercal:" << 30000 <<" now: " <<TTime::NowMS()<< std::endl;
//                                            task->Restart(); }, 30000);
//     sTaskMgr->Add(task1);
//     sTaskMgr->Add(task2);
//     sTaskMgr->Add(task3);
//     sTaskMgr->Add(task4);
// }
// int main(int argc, const char **argv)
// {

//     TestTask();
//     while (1)
//     {
//         sTaskMgr->OnWork();
//         std::this_thread::sleep_for(std::chrono::milliseconds(50));
//     }

//     return 0;
// }

// #include "base/LogStream.h"
// #include "base/Logger.h"
// #include "base/FileLog.h"
// #include "base/FileMgr.h"
// #include "base/TTime.h"
// #include <thread>
// #include "base/TaskMgr.h"
// using namespace tmms::base;

// std::thread t;

// void TestLog()
// {
//     t = std::thread([]()
//                     {
//         while (true)
//         {
//             LOG_INFO << "test info!!!" << TTime::NowMS();
//             LOG_DEBUG << " test debug!!!" << TTime::NowMS();
//             std::this_thread::sleep_for(std::chrono::microseconds(500));
//         } });
//     // LOG_TRACE << "test trace!!!";
//     // LOG_WARN << "test warn!!!";
//     // LOG_ERROR << "test error!!!";
// }
// int main(int argc, const char **argv)
// {
//     FileLogPtr log = sFileMgr->GetFileLog("test.log");
//     log->SetRotate(kRotateMinute);
//     tmms::base::g_logger = new Logger(log);
//     tmms::base::g_logger->SetLogLevel(kTrace);
//     TaskPtr task4 = std::make_shared<Task>([](const TaskPtr &task)
//                                            {
//                                                 sFileMgr->OnCheck();
//                                                 task->Restart();
//                                             }, 1000);
//     sTaskMgr->Add(task4);
//     TestLog();
//     while (1)
//     {
//         sTaskMgr->OnWork();
//         std::this_thread::sleep_for(std::chrono::milliseconds(50));
//     }
//     return 0;
// }

#include "base/Config.h"
#include "base/LogStream.h"
#include "base/FileMgr.h"
#include "base/TaskMgr.h"
#include <stdio.h>
#include <iostream>
#include <thread>
using namespace tmms::base;
int main(int argc, const char **argv)
{
    if (!sConfigMgr->LoadConfig("../config/config.json"))
    {
        std::cerr << "load config file failed." << std::endl;
        return -1;
    }
    ConfigPtr config = sConfigMgr->GetConfig();
    LogInfoPtr log_info = config->GetLogInfo();
    std::cout << "log level: " << log_info->level
              << " path: " << log_info->path
              << " name: " << log_info->name << std::endl;
    FileLogPtr log = sFileMgr->GetFileLog(log_info->path + log_info->name);
    if (!log)
    {
        std::cerr << "log can't open, exit." << std::endl;
        return -1;
    }
    log->SetRotate(log_info->rotate_type);
    g_logger = new Logger(log);
    g_logger->SetLogLevel(log_info->level);
    TaskPtr task4 = std::make_shared<Task>([](const TaskPtr &task)
                                           {
                                                sFileMgr->OnCheck();
                                                task->Restart(); }, 1000);
    while (1)
    {
        sTaskMgr->OnWork();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    return 0;
}