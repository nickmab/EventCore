#include "Logger.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace EventCore {

	Logger::log_sptr Logger::sLogger = nullptr;

	void Logger::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		sLogger = spdlog::stdout_color_mt("MABZ");
		sLogger->set_level(spdlog::level::trace);
		LOG_INFO("Logger initialized.");
	}

}