#pragma once

#include <memory>
#include <tuple>

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace EventCore {

	class Logger
	{
		using log_sptr = std::shared_ptr<spdlog::logger>;

	public:
		static void Init();
		inline static log_sptr& Get() { if (!sLogger) Init(); return sLogger; }

	private:
		static log_sptr sLogger;
	};

#ifdef BUILD_Debug
	#define ASSERTS_ENABLED 1
	#define VERBOSE_LOGGING 1
#elif defined BUILD_RelWithDebInfo
	#define ASSERTS_ENABLED 1
	#define NORMAL_LOGGING 1
#elif defined BUILD_Release
#else
	#error "Build configuration defines not provided!"
#endif

#if VERBOSE_LOGGING
#define _LOGF(level, fmt, ...) \
	::EventCore::Logger::Get()->##level("{}::{}()#{}: " fmt, \
			__FILE__ , __FUNCTION__, __LINE__, __VA_ARGS__)

#define _LOG(level, msg) \
	::EventCore::Logger::Get()->##level("{}::{}()#{}: {}", \
			__FILE__ , __FUNCTION__, __LINE__, msg)
#elif NORMAL_LOGGING
	#define _LOGF(level, fmt, ...) \
		::EventCore::Logger::Get()->##level(fmt, __VA_ARGS__)
	#define _LOG(level, msg) \
		::EventCore::Logger::Get()->##level(msg)
#else // The logging; it does nothing.
	#define _LOGF(level, fmt, ...)
	#define _LOG(level, msg)
#endif
	   
#define LOGF_TRACE(fmt, ...)    _LOGF(trace, fmt, __VA_ARGS__)
#define LOGF_INFO(fmt, ...)     _LOGF(info, fmt, __VA_ARGS__)
#define LOGF_WARN(fmt, ...)     _LOGF(warn, fmt, __VA_ARGS__)
#define LOGF_ERROR(fmt, ...)    _LOGF(error, fmt, __VA_ARGS__)
#define LOGF_CRITICAL(fmt, ...) _LOGF(critical, fmt, __VA_ARGS__)

#define LOG_TRACE(msg)    _LOG(trace, msg)
#define LOG_INFO(msg)     _LOG(info, msg)
#define LOG_WARN(msg)     _LOG(warn, msg)
#define LOG_ERROR(msg)    _LOG(error, msg)
#define LOG_CRITICAL(msg) _LOG(critical, msg)

#if ASSERTS_ENABLED
	#define ASSERTF(x, fmt, ...) { if (!(x)) { \
		LOGF_ERROR("Assertion failed: " fmt , __VA_ARGS__); \
		__debugbreak(); } }
	
	#define ASSERT(x, msg) { if (!(x)) { \
		LOG_ERROR("Assertion failed: " msg); \
		__debugbreak(); } }
#else // The assertions; they do nothing.
	#define ASSERTF(x, fmt, ...)
	#define ASSERT(x, msg)
#endif

}