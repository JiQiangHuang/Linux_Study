#include "TTime.h"
#include <sys/time.h>

using namespace tmms::base;
// 表示当前的UTC时间，单位是毫秒
int64_t TTime::NowMS()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

// 表示当前的UTC时间，单位是秒
int64_t TTime::Now()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec;
}

// 表示当前时间，返回当前的年月日时分秒
int64_t TTime::Now(int &year, int &month, int &day, int &hour, int &minute, int &second)
{
    struct tm tm;
    time_t t = time(NULL);
    localtime_r(&t, &tm);
    year = tm.tm_year + 1900;
    month = tm.tm_mon + 1;
    day = tm.tm_mday;
    hour = tm.tm_hour;
    minute = tm.tm_min;
    second = tm.tm_sec;
    return t;
}

// 表示返回当前时间ISO格式的字符串(yyyy-MM-ddTHH:mm:ss)
std::string TTime::ISOTime()
{
    struct timeval tv;
    struct tm tm;
    gettimeofday(&tv, NULL);
    time_t t = time(NULL);
    localtime_r(&t, &tm);
    char buf[128] = {0};
    auto n = sprintf(buf, "%4d-%02d-%02dT%02d:%02d:%02d",
                     tm.tm_year + 1900,
                     tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    return std::string(buf, buf + n);
}
