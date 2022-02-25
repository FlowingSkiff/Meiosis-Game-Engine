#pragma once

#include <spdlog/spdlog.h>
#include <memory>
#include <string_view>
class Logger
{
    public:
        static void Init();
        template<typename... ARGS>
        static void warn(std::string_view str, const ARGS&... args);
        template<typename... ARGS>
        static void info(std::string_view str, const ARGS&... args);
        template<typename... ARGS>
        static void debug(std::string_view str, const ARGS&... args);
        template<typename... ARGS>
        static void trace(std::string_view str, const ARGS&... args);
        template<typename... ARGS>
        static void error(std::string_view str, const ARGS&... args);
    private:
        static std::shared_ptr<spdlog::logger> clientLog;
};

template<typename... ARGS>
void Logger::warn(std::string_view str, const ARGS&... args)
{
    clientLog->warn(str, args...);
}

template<typename... ARGS>
void Logger::debug(std::string_view str, const ARGS&... args)
{
    clientLog->debug(str, args...);
}

template<typename... ARGS>
void Logger::trace(std::string_view str, const ARGS&... args)
{
    clientLog->trace(str, args...);
}

template<typename... ARGS>
void Logger::info(std::string_view str, const ARGS&... args)
{
    clientLog->info(str, args...);
}


template<typename... ARGS>
void Logger::error(std::string_view str, const ARGS&... args)
{
    clientLog->error(str, args...);
}