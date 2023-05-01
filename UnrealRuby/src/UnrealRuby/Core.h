#pragma once

#ifdef  UR_PLATFORM_WINDOWS
	#ifdef UR_BUILD_DLL
		#define UNREALRUBY_API __declspec(dllexport)
	#else
		#define UNREALRUBY_API __declspec(dllimport)
	#endif // 
#else
	#error Unreal Ruby only supports Windows!
#endif //  UR_PLATFORM_WINDOWS

#ifdef UR_ENABLE_ASSERTS
	#define UR_ASSERT(x, ...) {if(!(x)) {UR_ERROR("Assertion Failed: {0}",__VA_ARGS__); __debugbreak();}} 
	#define UR_CORE_ASSERT(x, ...) {if(!(x)) {UR_CORE_ERROR("Assertion Failed: {0}",__VA_ARGS__); __debugbreak();}}
#else
	#define UR_ASSERT(x, ...)
	#define UR_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1<<x)