#pragma once

#include "Meiosis/Core/Core.hpp"

#include <spdlog/spdlog.h>
#include <memory>
#include <string_view>
namespace Meiosis
{
class ME_API Logger
{
  public:
    static void init();

  public:
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

  public:
    template<typename... ARGS>
    static void coreWarn(std::string_view str, const ARGS&... args);
    template<typename... ARGS>
    static void coreInfo(std::string_view str, const ARGS&... args);
    template<typename... ARGS>
    static void coreDebug(std::string_view str, const ARGS&... args);
    template<typename... ARGS>
    static void coreTrace(std::string_view str, const ARGS&... args);
    template<typename... ARGS>
    static void coreError(std::string_view str, const ARGS&... args);


  private:
    static std::shared_ptr<spdlog::logger> clientLog;
    static std::shared_ptr<spdlog::logger> coreLog;
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

template<typename... ARGS>
void Logger::coreWarn(std::string_view str, const ARGS&... args)
{
    coreLog->warn(str, args...);
}

template<typename... ARGS>
void Logger::coreDebug(std::string_view str, const ARGS&... args)
{
    coreLog->debug(str, args...);
}

template<typename... ARGS>
void Logger::coreTrace(std::string_view str, const ARGS&... args)
{
    coreLog->trace(str, args...);
}

template<typename... ARGS>
void Logger::coreInfo(std::string_view str, const ARGS&... args)
{
    coreLog->info(str, args...);
}


template<typename... ARGS>
void Logger::coreError(std::string_view str, const ARGS&... args)
{
    coreLog->error(str, args...);
}


}// namespace Meiosis


#ifdef ENABLE_LOG

#define ENGINE_WARN(...) Meiosis::Logger::warn(__VA_ARGS__)
#define ENGINE_DEBUG(...) Meiosis::Logger::debug(__VA_ARGS__)
#define ENGINE_TRACE(...) Meiosis::Logger::trace(__VA_ARGS__)
#define ENGINE_INFO(...) Meiosis::Logger::info(__VA_ARGS__)
#define ENGINE_ERROR(...) Meiosis::Logger::error(__VA_ARGS__)

#define ME_ENGINE_WARN(...) Meiosis::Logger::coreWarn(__VA_ARGS__)
#define ME_ENGINE_DEBUG(...) Meiosis::Logger::coreDebug(__VA_ARGS__)
#define ME_ENGINE_TRACE(...) Meiosis::Logger::coreTrace(__VA_ARGS__)
#define ME_ENGINE_INFO(...) Meiosis::Logger::coreInfo(__VA_ARGS__)
#define ME_ENGINE_ERROR(...) Meiosis::Logger::coreError(__VA_ARGS__)
#else

#define ENGINE_WARN(...)
#define ENGINE_DEBUG(...)
#define ENGINE_TRACE(...)
#define ENGINE_INFO(...)
#define ENGINE_ERROR(...)

#define ME_ENGINE_WARN(...)
#define ME_ENGINE_DEBUG(...)
#define ME_ENGINE_TRACE(...)
#define ME_ENGINE_INFO(...)
#define ME_ENGINE_ERROR(...)
#endif