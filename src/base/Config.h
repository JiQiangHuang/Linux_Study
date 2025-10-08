#pragma once
#include "json/json.h"
#include "NonCopyable.h"
#include "Singleton.h"
#include "Logger.h"
#include "FileLog.h"
#include <string>
#include <cstdint>
#include <memory>
#include <mutex>
namespace tmms
{
    namespace base
    {
        struct LogInfo
        {
            LogLevel level;
            std::string path;
            std::string name;
            RotateType rotate_type{kRotateNone};
        };

        using LogInfoPtr = std::shared_ptr<LogInfo>;

        class Config
        {
        private:
            LogInfoPtr log_info_;

        public:
            Config() = default;
            ~Config() = default;

            bool Loadconfig(const std::string &file);
            bool ParseLogInfo(const Json::Value &root);
            LogInfoPtr &GetLogInfo();

            std::string name_;
            int32_t cpu_start_{0};
            int32_t thread_nums_{1};
        };

        using ConfigPtr = std::shared_ptr<Config>;

        class ConfigMgr : public NonCopyable
        {
        private:
            ConfigPtr config_;
            std::mutex lock_;

        public:
            ConfigMgr() = default;
            ~ConfigMgr() = default;

            bool LoadConfig(const std::string &file);
            ConfigPtr GetConfig();
        };

#define sConfigMgr tmms::base::Singleton<tmms::base::ConfigMgr>::Instance()
    }
}