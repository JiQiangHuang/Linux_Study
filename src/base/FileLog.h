#pragma once
#include <string>
#include <memory>
namespace tmms
{
    namespace base
    {
        enum RotateType
        {
            kRotateNone,
            kRotateMinute,
            kRotateHour,
            kRotateDay,
        };
        class FileLog
        // 1.filelog的成员变量包括文件路径、文件描述符和日志切分类型。
        // 2.成员函数包括打开文件、写入日志、切分日志和返回文件长度。
        {
        private:
            int fd_{-1};
            std::string file_path_;
            RotateType rotate_type_;

        public:
            FileLog() = default;
            ~FileLog() = default;

            // 打开文件
            bool Open(const std::string &filePath);
            // 写入日志
            size_t WriteLog(const std::string &msg);
            // 切分
            void Rotate(const std::string &file);
            // 设置切分类型
            void SetRotate(RotateType type);
            // 获取切分类型
            RotateType GetRotateType() const;
            // 获取文件大小
            int64_t FileSize() const;
            // 获取文件路径
            std::string FilePath() const;
        };
        using FileLogPtr = std::shared_ptr<FileLog>;

    } // namespace base

} // namespace tmms
