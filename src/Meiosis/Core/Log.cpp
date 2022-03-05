#include "Meiosis/Core/Log.hpp"

#include "spdlog/sinks/stdout_color_sinks.h"


namespace Meiosis
{
std::shared_ptr<spdlog::logger> Logger::clientLog;
std::shared_ptr<spdlog::logger> Logger::coreLog;

void Logger::init()
{
    spdlog::set_pattern("%^[%n %l %D %X] %v%$");
    clientLog = spdlog::stdout_color_mt("client");
    clientLog->set_level(spdlog::level::trace);
    coreLog = spdlog::stdout_color_mt("core");
    coreLog->set_level(spdlog::level::trace);
}
}// namespace Meiosis