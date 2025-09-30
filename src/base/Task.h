#pragma once
#include <cstdint>
#include <functional>
#include <memory>

// 1.定时任务是后台系统中不可或缺的功能，用于定时或重复完成某些任务。
// 2.定时任务的两个主要特性：规定的时间点和时间间隔。
// 3.定时任务可以单次执行或重复执行。
// 4.定时任务通过回调函数执行，初始化时传入回调函数。
namespace tmms
{
    namespace base
    {
        class Task;
        using TaskPtr = std::shared_ptr<Task>;
        using TaskCallback = std::function<void(const TaskPtr &)>;
        class Task : public std::enable_shared_from_this<Task>
        {
            // 1.设计成员变量：时间点、时间间隔、回调函数。
            // 2.构造函数：传入回调函数和时间间隔。
            // 3.重复执行任务的方法：list_star。
        private:
            int64_t interval_{0};
            int64_t when_{0};
            TaskCallback cb_;

        public:
            Task(const TaskCallback &cb, int64_t interval);
            Task(const TaskCallback &&cb, int64_t interval);

            void Run();
            void Restart();
            int64_t When() const
            {
                return when_;
            }
        };

    } // namespace name

} // namespace tmms
