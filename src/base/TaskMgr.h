#pragma once
#include "Task.h"
#include "Singleton.h"
#include <unordered_set>
#include <mutex>
// 1.任务管理器存放所有定时任务，并管理任务的添加、删除。
// 2.检测任务时间并执行任务。
// 3.保证定时任务的全局唯一性。
// 4.介绍几种常用的算法：直接遍历、最小时间堆、时间轮。

// 直接遍历算法
// 1.简单遍历任务列表，检测任务是否到点。
// 2.如果任务到点，则执行任务并更新任务时间。
// 3.直接遍历算法的时间复杂度为ON。

// 最小时间堆算法
// 1.最小时间堆是一个完全二叉树，堆顶时间是最小的。
// 2.总是取堆顶任务判断，如果时间未到点，则退出循环。
// 3.如果时间到点，则执行任务并更新时间点，重建堆。
// 4.最小时间堆算法的插入和删除复杂度为logn，遍历复杂度为ON。

// 时间轮算法
// 1.时间轮像一个钟表，表针转动到哪一格就执行该格上的任务。
// 2.右边轮转动一圈后，左边轮转动一格，依次类推。
// 3.时间轮使用的容器包括向量、队列和任务列表。
// 4.插入和删除复杂度为常量，遍历复杂度为常量。
namespace tmms
{
    namespace base
    {
        class TaskMgr : public NonCopyable
        {
        private:
            std::unordered_set<TaskPtr> tasks_;
            std::mutex lock_;

        public:
            TaskMgr() = default;
            ~TaskMgr() = default;

            void OnWork();
            bool Add(TaskPtr &task);
            bool Del(TaskPtr &task);
        };
    }
    #define sTaskMgr tmms::base::Singleton<tmms::base::TaskMgr>::Instance()
}