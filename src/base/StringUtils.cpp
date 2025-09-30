#include "StringUtils.h"
using namespace tmms::base;

// 前缀匹配：检查子串是否与字符串的前缀匹配，返回布尔值。
bool StringUtils::StartsWith(const string &s, const string &sub)
{
    if (sub.empty())
    {
        return true;
    }
    if (s.empty())
    {
        return false;
    }
    auto len = s.size();
    auto slen = sub.size();
    if (len < slen)
    {
        return false;
    }

    return s.compare(0, slen, sub) == 0;
}

// 后缀匹配：检查子串是否与字符串的后缀匹配，返回布尔值。
bool StringUtils::EndWith(const string &s, const string &sub)
{
    if (sub.empty())
    {
        return true;
    }
    if (s.empty())
    {
        return false;
    }
    auto len = s.size();
    auto slen = sub.size();
    if (len < slen)
    {
        return false;
    }

    return s.compare(len - slen, slen, sub) == 0;
}

// 返回文件路径：获取传入完整路径中的当前文件目录。
std::string StringUtils::FilePath(const std::string &path)
{
    auto pos = path.find_last_of("/\\");
    if (pos != std::string::npos)
    {
        return path.substr(0, pos);
    }
    else
    {
        return "./";
    }
}

// 获取文件名及后缀：从完整路径中提取文件名和文件后缀。
std::string StringUtils::FileNameExt(const std::string &path)
{
    string file_name;
    auto pos = path.find_last_of("/\\");
    if (pos != std::string::npos)
    {
        if (pos + 1 < path.size())
        {
            return path.substr(pos + 1);
        }
    }
    return path;
}

// 获取文件名：去除文件后缀，获取文件名。
std::string StringUtils::FileName(const std::string &path)
{
    string file_name = FileNameExt(path);
    auto pos = path.find_last_of(".");
    if (pos != std::string::npos)
    {
        if (pos != 0)
        {
            return file_name.substr(0, pos);
        }
    }
    return file_name;
}

// 获取文件后缀：提取文件名的后缀部分。
std::string StringUtils::Extension(const std::string &path)
{
    string file_name = FileNameExt(path);
    auto pos = path.find_last_of(".");
    if (pos != std::string::npos)
    {
        if (pos != 0 && pos + 1 < file_name.size())
        {
            return file_name.substr(pos + 1);
        }
    }
    return std::string();
}

// 接受一个分割符，返回一个字符串列表。
std::vector<std::string> StringUtils::Splitstring(const string &s, const string &delimiter)
{
    if (delimiter.empty())
    {
        return std::vector<std::string>();
    }
    std::vector<std::string> result;
    size_t last = 0;
    size_t next = 0;
    while ((next = s.find(delimiter, last) != std::string::npos))
    {
        if (next > last)
        {
            result.emplace_back(s.substr(last, next = last));
        }
        last = next + delimiter.size();
    }
    if (last < s.size())
    {
        result.emplace_back(s.substr(last));
    }
    return result;
}