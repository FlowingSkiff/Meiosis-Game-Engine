#pragma once

#include "Genesis/Core/Core.hpp"

#include <spdlog/spdlog.h>
#include <memory>
#include <string_view>
namespace Genesis
{
class GN_API Logger
{
  public:
    static void init();
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


}// namespace Genesis


#ifdef ENABLE_LOG
#define ENGINE_WARN(...) Genesis::Logger::warn(__VA_ARGS__)
#define ENGINE_DEBUG(...) Genesis::Logger::debug(__VA_ARGS__)
#define ENGINE_TRACE(...) Genesis::Logger::trace(__VA_ARGS__)
#define ENGINE_INFO(...) Genesis::Logger::info(__VA_ARGS__)
#define ENGINE_ERROR(...) Genesis::Logger::error(__VA_ARGS__)
#else
#define ENGINE_WARN(...)
#define ENGINE_DEBUG(...)
#define ENGINE_TRACE(...)
#define ENGINE_INFO(...)
#define ENGINE_ERROR(...)
#endif