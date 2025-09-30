#include "FileMgr.h"
#include "TTime.h"
#include "StringUtils.h"
#include <sstream>
using namespace tmms::base;
namespace
{
    static tmms::base::FileLogPtr file_log_nullptr;
} 

void FileMgr::OnCheck()
{
    bool day_change{false};
    bool hour_change{false};
    bool minute_change{false};
    int year = 0, month = 0, day = -1, hour = -1, minute = 0, second = 0;
    TTime::Now(year, month, day, hour, minute, second);
    if (last_day_ == -1)
    {
        last_day_ = day;
        last_hour_ = hour;
        last_minute_ = minute;
        last_year_ = year;
        last_month_ = month;
    }
    if (last_day_ != day)
    {
        day_change = true;
    }
    if (last_hour_ != hour)
    {
        hour_change = true;
    }
    if (last_minute_ != minute)
    {
        minute_change = true;
    }
    if (!day_change && !hour_change && !minute_change)
    {
        return;
    }
    std::lock_guard<std::mutex> lk(lock_);
    for (auto &l : logs_)
    {
        if (minute_change && l.second->GetRotateType() == kRotateMinute)
            RotateMinutes(l.second);
        if (hour_change && l.second->GetRotateType() == kRotateHour)
            RotateHours(l.second);
        if (day_change && l.second->GetRotateType() == kRotateDay)
            RotateDays(l.second);
    }
    last_day_ = day;
    last_hour_ = hour;
    last_minute_ = minute;
    last_year_ = year;
    last_month_ = month;
}

// 1.获取日志文件路径，判断路径是否存在，不存在则创建。
// 2.打开日志文件，如果打开失败则返回空。
// 3.成功打开后将日志文件添加到管理队列中。
FileLogPtr FileMgr::GetFileLog(const std::string &file_name)
{
    std::lock_guard<std::mutex> lk(lock_);
    auto iter = logs_.find(file_name);
    if (iter != logs_.end())
        return iter->second;
    FileLogPtr log = std::make_shared<FileLog>();
    if (!log->Open(file_name))
        return file_log_nullptr;
    logs_.emplace(file_name, log);
    return log;
}

// 1.从管理队列中移除日志文件，但不关闭文件。
// 2.其他线程可能正在使用该文件，因此无法关闭。
void FileMgr::RemoveFileLog(const FileLogPtr &log)
{
    std::lock_guard<std::mutex> lk(lock_);
    logs_.erase(log->FilePath());
}

// 1.判断文件大小是否大于零，小于等于零的文件无需切分。
// 2.生成新的文件名，包括原文件名、日期后缀。
// 3.调用FileLog的函数进行切分。
void FileMgr::RotateDays(const FileLogPtr &file)
{
    if (file->FileSize() > 0)
    {
        char buf[128] = {
            0,
        };
        sprintf(buf, "_%4d-%02d-%02d.", last_year_, last_month_, last_day_);
        std::string file_path = file->FilePath();
        std::string path = StringUtils::FilePath(file_path);
        std::string file_name = StringUtils::FileName(file_path);
        std::string file_ext = StringUtils::Extension(file_path);
        std::ostringstream ss;
        ss << path
           << file_name
           << buf
           << file_ext;
        file->Rotate(ss.str());
    }
}

// 1.生成新的文件名，包括原文件名、时间后缀。
// 2.调用FileLog的函数进行切分。
void FileMgr::RotateHours(const FileLogPtr &file)
{
    if (file->FileSize() > 0)
    {
        char buf[128] = {
            0,
        };
        sprintf(buf, "_%4d-%02d-%02dT%02d.", last_year_, last_month_, last_day_, last_hour_);
        std::string file_path = file->FilePath();
        std::string path = StringUtils::FilePath(file_path);
        std::string file_name = StringUtils::FileName(file_path);
        std::string file_ext = StringUtils::Extension(file_path);
        std::ostringstream ss;
        ss << path
           << file_name
           << buf
           << file_ext;
        file->Rotate(ss.str());
    }
}


// 1.生成新的文件名，包括原文件名、时间后缀。
// 2.调用FileLog的函数进行切分。
void FileMgr::RotateMinutes(const FileLogPtr &file)
{
    if (file->FileSize() > 0)
    {
        char buf[128] = {
            0,
        };
        sprintf(buf, "_%4d-%02d-%02dT%02d-%02d.", last_year_, last_month_, last_day_, last_hour_, last_minute_);
        std::string file_path = file->FilePath();
        std::string path = StringUtils::FilePath(file_path);
        std::string file_name = StringUtils::FileName(file_path);
        std::string file_ext = StringUtils::Extension(file_path);
        std::ostringstream ss;
        ss << path
           << file_name
           << buf
           << file_ext;
        file->Rotate(ss.str());
    }
}