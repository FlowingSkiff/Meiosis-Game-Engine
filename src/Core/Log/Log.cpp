#include "Core/Log/Log.hpp"

#include "spdlog/sinks/stdout_color_sinks.h"

std::shared_ptr<spdlog::logger> clientLog;

void Logger::Init()
{
    spdlog::set_pattern("[%l] %D %X: %v");
    clientLog = spdlog::stdout_color_mt("console");
}

