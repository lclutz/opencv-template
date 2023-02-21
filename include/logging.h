#pragma once

#include <format>
#include <stdio.h>
#include <string>
#include <iostream>
#include <string_view>

#if WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

enum LogLevel
{
    LOG_ERROR,
    LOG_WARNING,
    LOG_INFO,
};

static LogLevel LOG_LEVEL = LOG_INFO;

static void log(std::string_view message) {
    std::cerr << message;
#if WIN32
    OutputDebugStringA(std::string(message).c_str());
#endif
}

template <typename... Args>
void log(std::string_view prefix, std::string_view fmt, Args&&... args)
{
    log(std::vformat(std::format("[{}]: {}\n", prefix, fmt), std::make_format_args(args...)));
}

template <typename... Args>
void logi(std::string_view fmt, Args&&... args)
{
    if (LOG_LEVEL >= LOG_INFO) {
        log("INFO", fmt, args...);
    }
}

template <typename... Args>
void logw(std::string_view fmt, Args&&... args)
{
    if (LOG_LEVEL >= LOG_WARNING) {
        log("WARNING", fmt, args...);
    }
}

template <typename... Args>
void loge(std::string_view fmt, Args&&... args)
{
    if (LOG_LEVEL >= LOG_ERROR) {
        log("ERROR", fmt, args...);
    }
}
