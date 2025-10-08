#include "Config.h"
#include "LogStream.h"
#include <fstream>
using namespace tmms::base;

bool Config::Loadconfig(const std::string &file)
{
    LOG_DEBUG << "config file: " << file;
    Json::CharReaderBuilder reader;
    std::ifstream in(file);
    Json::Value root;
    std::string err;
    auto ok = Json::parseFromStream(reader, in, &root, &err);
    if (!reader.parse(file, root))
    {
        LOG_ERROR << "config file: " << file << " parse error: " << err;
    }

    Json::Value nameObj = root["name"];
    if (!nameObj.isNull())
    {
        name_ = nameObj.asString();
    }

    Json::Value cpusObj = root["cpu_start"];
    if (!cpusObj.isNull())
    {
        cpu_start_ = cpusObj.asInt();
    }

    Json::Value threadsObj = root["threads"];
    if (!threadsObj.isNull())
    {
        thread_nums_ = threadsObj.asInt();
    }

    Json::Value logObj = root["log"];
    if (!logObj.isNull())
    {
        ParseLogInfo(logObj);
    }
}

bool Config::ParseLogInfo(const Json::Value &root)
{
    log_info_ = std::make_shared<LogInfo>();

    Json::Value levelObj = root["level"];
    if (!levelObj.isNull())
    {
        std::string level = levelObj.asString();
        if (level == "TRACE")
        {
            log_info_->level = kTrace;
        }
        else if (level == "DEBUG")
        {
            log_info_->level = kDebug;
        }
        else if (level == "INFO")
        {
            log_info_->level = kInfo;
        }
        else if (level == "WARN")
        {
            log_info_->level = kWarn;
        }
        else if (level == "ERROR")
        {
            log_info_->level = kError;
        }
    }

    Json::Value rtObj = root["rotate"];
    if (!rtObj.isNull())
    {
        std::string rt = rtObj.asString();
        if (rt == "DAY")
        {
            log_info_->rotate_type = kRotateDay;
        }
        else if (rt == "HOUR")
        {
            log_info_->rotate_type = kRotateHour;
        }
        else if (rt == "MINUTE")
        {
            log_info_->rotate_type = kRotateMinute;
        }
    }

    Json::Value nameObj = root["name"];
    if (!nameObj.isNull())
    {
        log_info_->name = nameObj.asString();
    }

    Json::Value pathObj = root["path"];
    if (!pathObj.isNull())
    {
        log_info_->path = pathObj.asString();
    }
}

LogInfoPtr &Config::GetLogInfo()
{
    return log_info_;
}

bool ConfigMgr::LoadConfig(const std::string &file)
{
    LOG_DEBUG << " load config file: " << file;
    ConfigPtr config = std::make_shared<Config>();
    if (config->Loadconfig(file))
    {
        std::lock_guard<std::mutex> lk(lock_);
        config_ = config;
        return true;
    }
    return false;
}
ConfigPtr ConfigMgr::GetConfig()
{
    std::lock_guard<std::mutex> lk(lock_);
    return config_;
}