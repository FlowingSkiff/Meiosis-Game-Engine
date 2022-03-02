#include "Genesis/Core/Log/Log.hpp"

#include "spdlog/sinks/stdout_color_sinks.h"


namespace Genesis
{
std::shared_ptr<spdlog::logger> Logger::clientLog;

void Logger::init()
{
    // spdlog::set_pattern("[%l] %D %X: %v");
    clientLog = spdlog::stdout_color_mt("console");
    clientLog->set_level(spdlog::level::trace);
}
}// namespace Genesis