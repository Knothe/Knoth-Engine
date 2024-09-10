#pragma once

#ifdef KNOTH_PLATFORM_WINDOWS
	#ifdef KNOTH_BUILD_DLL
		#define KNOTH_API __declspec(dllexport)
	#else
		#define KNOTH_API __declspec(dllimport)
	#endif
#else
	#error Only support windows
#endif

#ifdef GLE_ENABLE_ASSERTS
	#define KNOTH_ASSERT(x, ...) {if(!(x)){GLE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
	#define KNOTH_CORE_ASSERT(x, ...) {if(!(x)){GLE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS_); __debugbreak();}}
#else
	#define KNOTH_ASSERT(x, ...)
	#define KNOTH_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)