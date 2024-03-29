#pragma once

#include "Core.h"

#include <spdlog/spdlog.h>

namespace Engine
{
	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core Log Macros
#define CORE_LOG_TRACE(...)    Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CORE_LOG_INFO(...)     Log::GetCoreLogger()->info(__VA_ARGS__)
#define CORE_LOG_WARN(...)     Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CORE_LOG_ERROR(...)    Log::GetCoreLogger()->error(__VA_ARGS__)
#define CORE_LOG_FATAL(...)    Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client Log Macros
#define LOG_TRACE(...)    Engine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...)     Engine::Log::GetClientLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)     Engine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)    Engine::Log::GetClientLogger()->error(__VA_ARGS__)
#define LOG_FATAL(...)    Engine::Log::GetClientLogger()->critical(__VA_ARGS__)
