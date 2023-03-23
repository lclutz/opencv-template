#pragma once

#include <string>

#if _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include "fmt/core.h"

enum LogLevel
{
    LOG_ERROR,
    LOG_WARNING,
    LOG_INFO,
};

static LogLevel GLOBAL_LOG_LEVEL = LOG_INFO;

static void log(const std::string &message)
{
    fmt::print(stderr, message);
#if _WIN32
    OutputDebugStringA(std::string(message).c_str());
#endif
}

template <typename... Args>
static void log(const std::string &prefix, const std::string &fmt, const Args&... args)
{
    log(fmt::format(fmt::format("[{}]: {}\n", prefix, fmt), args...));
}

template <typename T, typename... Args>
static void logi(const T &fmt, const Args&... args)
{
    if (GLOBAL_LOG_LEVEL >= LOG_INFO) {
        log("INFO", fmt, args...);
    }
}

template <typename T, typename... Args>
static void logw(const T &fmt, const Args&... args)
{
    if (GLOBAL_LOG_LEVEL >= LOG_WARNING) {
        log("WARNING", fmt, args...);
    }
}

template <typename T, typename... Args>
static void loge(const T &fmt, const Args&... args)
{
    if (GLOBAL_LOG_LEVEL >= LOG_ERROR) {
        log("ERROR", fmt, args...);
    }
}
