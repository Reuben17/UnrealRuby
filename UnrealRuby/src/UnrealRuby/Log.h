#pragma once
#include "Core.h"
#include "spdlog/spdlog.h"
#include <memory>
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace UnrealRuby
{
	class UNREALRUBY_API Log
	{
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	};

}

//Core Log Macros
#define UR_CORE_TRACE(...)  ::UnrealRuby::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define UR_CORE_INFO(...)   ::UnrealRuby::Log::GetCoreLogger()->info(__VA_ARGS__)
#define UR_CORE_WARN(...)   ::UnrealRuby::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define UR_CORE_ERROR(...)  ::UnrealRuby::Log::GetCoreLogger()->error(__VA_ARGS__)
#define UR_CORE_FATAL(...)  ::UnrealRuby::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//Client Log Macros
#define UR_TRACE(...)  ::UnrealRuby::Log::GetClientLogger()->trace(__VA_ARGS__)
#define UR_INFO(...)   ::UnrealRuby::Log::GetClientLogger()->info(__VA_ARGS__)
#define UR_WARN(...)   ::UnrealRuby::Log::GetClientLogger()->warn(__VA_ARGS__)
#define UR_ERROR(...)  ::UnrealRuby::Log::GetClientLogger()->error(__VA_ARGS__)
#define UR_FATAL(...)  ::UnrealRuby::Log::GetClientLogger()->fatal(__VA_ARGS__)




