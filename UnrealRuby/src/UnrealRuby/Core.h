#pragma once

#include <memory>  

#ifdef  UR_PLATFORM_WINDOWS
#if UR_DYNAMIC_LINK  
	#ifdef UR_BUILD_DLL 
		#define UNREALRUBY_API __declspec(dllexport)
	#else
		#define UNREALRUBY_API __declspec(dllimport)
	#endif // 
#else
#define UNREALRUBY_API
#endif
#else
	#error Unreal Ruby only supports Windows!
#endif //  UR_PLATFORM_WINDOWS

#ifdef UR_DEBUG
#define UR_ENABLE_ASSERTS
#endif

#ifdef UR_ENABLE_ASSERTS 
	#define UR_ASSERT(x, ...) {if(!(x)) {UR_ERROR("Assertion Failed: {0}",__VA_ARGS__); __debugbreak();}} 
	#define UR_CORE_ASSERT(x, ...) {if(!(x)) {UR_CORE_ERROR("Assertion Failed: {0}",__VA_ARGS__); __debugbreak();}}
#else
	#define UR_ASSERT(x, ...)
	#define UR_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1<<x)

#define UR_BIND_EVENT_FN(fn) std::bind(&fn,this,std::placeholders::_1) 

namespace UnrealRuby {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

}