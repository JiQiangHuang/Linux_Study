#pragma once
#include "FileLog.h"
#include <memory>
#include <unordered_map>
#include <mutex>
namespace tmms
{
    namespace base
    {
        class FileMgr
        {
        private:
            std::unordered_map<std::string,FileLogPtr> logs_;
            std::mutex lock_;
            int last_day_{-1};
            int last_hour_{-1};
            int last_minute_{-1};
            int last_year_{-1};
            int last_month_{-1};
        public:
            FileMgr() =default;
            ~FileMgr()=default;
            
            // 检测日志文件是否需要切分，通过定时任务定期检测。
            void OnCheck();
            // 日志文件获取
            FileLogPtr GetFileLog(const std::string &filename);
            // 日志文件删除
            void RemoveFileLog(const FileLogPtr &log);
            // 日志文件按天切分
            void RotateDays(const FileLogPtr &file);
            // 日志文件按小时切分
            void RotateHours(const FileLogPtr &file);
            // 日志文件按分钟切分
            void RotateMinutes(const FileLogPtr &file);
        };

    } // namespace base

} // namespace tmms

#define sFileMgr tmms::base::Singleton<tmms::base::FileMgr>::Instance()
