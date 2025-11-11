#include "SimpleLog.h"

LogLevel logLevel = kLogLevel_All;

#ifdef ANDROID
// 定义一个替代 printf 的函数
void android_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    __android_log_vprint(ANDROID_LOG_INFO, "MyTag", format, args);
    va_end(args);
}
#endif

// 获取当前时间的跨平台函数
void getCurrentTime(char *buffer, size_t bufferSize)
{
#ifdef CC_PLUGIN_WASM
    struct tm tmTime;
    struct timeb tb;

    ftime(&tb);
    localtime_r(&tb.time, &tmTime);

    if (1)
    {
        int tmYear = tmTime.tm_year + 1900;
        int tmMon = tmTime.tm_mon + 1;
        int tmMday = tmTime.tm_mday;
        int tmHour = tmTime.tm_hour;
        int tmMin = tmTime.tm_min;
        int tmSec = tmTime.tm_sec;
        int tmMillisec = tb.millitm;
        snprintf(buffer, bufferSize, "%d-%02d-%02d %02d:%02d:%02d.%03d", tmYear, tmMon, tmMday, tmHour, tmMin, tmSec, tmMillisec);
    }
#elif CC_PLUGIN_NATIVE
    struct timeval tv;
    gettimeofday(&tv, NULL);
    struct tm *tmTime = localtime(&tv.tv_sec);
    int tmYear = tmTime->tm_year + 1900;
    int tmMon = tmTime->tm_mon + 1;
    int tmMday = tmTime->tm_mday;
    int tmHour = tmTime->tm_hour;
    int tmMin = tmTime->tm_min;
    int tmSec = tmTime->tm_sec;
    int tmMillisec = tv.tv_usec / 1000;
    snprintf(buffer, bufferSize, "%d-%02d-%02d %02d:%02d:%02d.%03d", tmYear, tmMon, tmMday, tmHour, tmMin, tmSec, tmMillisec);

#endif
}

void simpleLog(const char *format, ...)
{
    if (logLevel == kLogLevel_None)
    {
        return;
    }

    char szBuffer[1024] = {0};
    char szTime[32] = {0};
    char *p = NULL;
    int prefixLength = 0;
    const char *tag = "Core";

    // 获取当前时间并格式化为字符串
    getCurrentTime(szTime, sizeof(szTime));

    // 添加前缀（时间戳和标签）
    prefixLength = snprintf(szBuffer, sizeof(szBuffer), "[%s][%s][DT] ", szTime, tag);
    p = szBuffer + prefixLength;

    prefixLength = sprintf(szBuffer, "[%s][%s][DT] ", szTime, tag);
    p = szBuffer + prefixLength;

    if (1)
    {
        va_list ap;
        va_start(ap, format);
        vsnprintf(p, 1024 - prefixLength, format, ap);
        va_end(ap);
    }
#ifdef ANDROID
    android_printf("%s\n", szBuffer);
#else
    printf("%s\n", szBuffer);
#endif
}
