#include "pch.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace EventCore {

	Logger::log_sptr Logger::sLogger = nullptr;

	void Logger::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		sLogger = spdlog::stdout_color_mt("MABZ");
#if VERBOSE_LOGGING
		sLogger->set_level(spdlog::level::trace);
#elif NORMAL_LOGGING
		sLogger->set_level(spdlog::level::info);
#elif MINIMAL_LOGGING
		sLogger->set_level(spdlog::level::warn);
#else
	#error "Have not specified a recognised logging level."
#endif
		LOG_INFO("Logger initialized.");
	}

}