#pragma once

#include <string>
#include <vector>
namespace tmms
{
    namespace base
    {
        using std::string;
        class StringUtils
        {
        public:
            // 前缀匹配：检查子串是否与字符串的前缀匹配，返回布尔值。
            static bool StartsWith(const string &s, const string &sub);
            // 后缀匹配：检查子串是否与字符串的后缀匹配，返回布尔值。
            static bool EndWith(const string &s, const string &sub);

            // 返回文件路径：获取传入完整路径中的当前文件目录。
            static std::string FilePath(const std::string &path);
            // 获取文件名及后缀：从完整路径中提取文件名和文件后缀。
            static std::string FileNameExt(const std::string &path);
            // 获取文件名：去除文件后缀，获取文件名。
            static std::string FileName(const std::string &path);
            // 获取文件后缀：提取文件名的后缀部分。
            static std::string Extension(const std::string &path);
            
            // 接受一个分割符，返回一个字符串列表。
            static std::vector<std::string> Splitstring(const string &s,const string &delimiter);
        };
    } // namespace base

}