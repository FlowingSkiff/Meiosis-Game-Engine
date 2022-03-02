#include "Genesis/Core/Log/Log.hpp"

#include "spdlog/sinks/stdout_color_sinks.h"


namespace Genesis
{
std::shared_ptr<spdlog::logger> Logger::clientLog;

void Logger::Init()
{
    // spdlog::set_pattern("[%l] %D %X: %v");
    clientLog = spdlog::stdout_color_mt("console");
}

void Logger::print()
{
    clientLog->trace("Test");
}
}// namespace Genesis