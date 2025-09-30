#pragma once
#include "NonCopyable.h"
#include "FileLog.h"
#include <string>
namespace tmms
{
    namespace base
    {
        // 1.日志级别包括trace、debug、info、warning和error。
        // 2.trace和debug用于开发阶段，输出较多信息。
        // 3.info、warning和error用于生产环境，输出关键信息。
        enum LogLevel
        {
            kTrace,
            kDebug,
            kInfo,
            kWarn,
            kError,
            kMaxNumOfLogLevel,
        };
        // 1.log类包括成员变量和成员函数，成员变量包括日志输出等级和日志输出对象。
        // 2.成员函数包括构造函数、设置日志等级、获取日志等级和输出日志。
        class Logger : public NonCopyable
        {
        private:
            LogLevel level_{kDebug};
            FileLogPtr log_;
        public:
            Logger(const FileLogPtr &log);
            ~Logger() = default;

            void SetLogLevel(const LogLevel &level);
            LogLevel GetLogLevel() const;
            void Write(const std::string &msg);
        };

    } // namespace name

} // namespace tmms
