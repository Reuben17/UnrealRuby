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

#define BIT(x) (1<<x)